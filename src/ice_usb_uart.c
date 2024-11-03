//
// Created by MrJake222 on 03/11/24.
//

#include "ice_usb_uart.h"

#include "rb.h"
#include "hardware/uart.h"
#include "hardware/irq.h"
#include "hardware/dma.h"
#include "hardware/timer.h"

struct uart_wrap {
    int itf;            // CDC interface number
    uart_inst_t* inst;  // pico sdk instance reference

    struct rb rx_buf;
    struct rb tx_buf;

    absolute_time_t dbg_time;

    int dma_chA;
    int dma_chB;
    int dma_flush_alarm;
    absolute_time_t dma_last_transfer;
    void (*dma_flush_alarm_cb)();
};


// ------------------------------- Rx functions -------------------------------
// uart -> rb (irq)
//   rb -> cdc

#define DMA_TCNT        512
#define DMA_ALARM_US    (100*1000) // 100 ms

static void ice_usb_uart_rx_dma_irq0(struct uart_wrap* uart, int channel) {
    rb_write_ack(&uart->rx_buf, DMA_TCNT);

    // complementary channel will write to write_ptr
    // need to skip another ack
    char* waddr = rb_write_ptr_next_ack(&uart->rx_buf, DMA_TCNT);
    dma_channel_set_write_addr(channel, waddr, false);

    uart->dma_last_transfer = get_absolute_time();
}

static void ice_usb_uart_dma_channels_enable(struct uart_wrap* uart, int en) {
    if (en) {
        dma_channel_hw_addr(uart->dma_chA)->al1_ctrl |= DMA_CH0_CTRL_TRIG_EN_BITS;
        dma_channel_hw_addr(uart->dma_chB)->al1_ctrl |= DMA_CH0_CTRL_TRIG_EN_BITS;
    }
    else {
        dma_channel_hw_addr(uart->dma_chA)->al1_ctrl &= ~DMA_CH0_CTRL_TRIG_EN_BITS;
        dma_channel_hw_addr(uart->dma_chB)->al1_ctrl &= ~DMA_CH0_CTRL_TRIG_EN_BITS;
    }
}

static void ice_usb_uart_dma_flush_alarm(struct uart_wrap* uart) {
    uint elapsed_us = absolute_time_diff_us(uart->dma_last_transfer, get_absolute_time());

    if (elapsed_us >= (DMA_ALARM_US*9/10)) {
        // pause channels, capture state as atomically as possible
        ice_usb_uart_dma_channels_enable(uart, 0);

        int ch_busy, ch_other;
        if (dma_channel_is_busy(uart->dma_chA)) {
            ch_busy = uart->dma_chA;
            ch_other = uart->dma_chB;
        }
        else if (dma_channel_is_busy(uart->dma_chB)) {
            ch_busy = uart->dma_chB;
            ch_other = uart->dma_chA;
        }
        else {
            // can't return, need to set alarm
            goto end;
        }

        int tr_left = (int) dma_channel_hw_addr(ch_busy)->transfer_count;
        int tr_done = DMA_TCNT - tr_left;

        if (tr_done == 0)
            goto end;

        // abort the active channel, with errata mitigation
        dma_channel_set_irq0_enabled(ch_busy, false);
        dma_channel_abort(ch_busy);
        dma_channel_acknowledge_irq0(ch_busy);
        dma_channel_set_irq0_enabled(ch_busy, true);

        // re-enable, won't start yet because the active one got aborted
        ice_usb_uart_dma_channels_enable(uart, 1);

        // ack already done bytes
        rb_write_ack(&uart->rx_buf, tr_done);
        char* wptr_busy  = rb_write_ptr(&uart->rx_buf);
        char* wptr_other = rb_write_ptr_next_ack(&uart->rx_buf, DMA_TCNT);

        // wptr_busy can cross over the end of the buffer
        // but we've configured ring size and alignment

        // set up the channels with new pointer and transfer count
        dma_channel_set_write_addr(ch_other, wptr_other, false);
        dma_channel_set_write_addr(ch_busy, wptr_busy, false);
        dma_channel_set_trans_count(ch_busy, DMA_TCNT, true);

        uart->dma_last_transfer = get_absolute_time();
        // printf("elapsed %dms ack %d\n", elapsed_us/1000, tr_done);
    }
    // else printf("No\n");

end:
    // re-enable here also, in case of goto got here
    ice_usb_uart_dma_channels_enable(uart, 1);
    hardware_alarm_set_target(uart->dma_flush_alarm, delayed_by_us(get_absolute_time(), DMA_ALARM_US));
}

static void ice_usb_uart_rx_conf_dma_chan(struct uart_wrap* uart, int dma_chan, char* data, uint count, int chain_to) {
    dma_channel_config c = dma_channel_get_default_config(dma_chan);
    channel_config_set_transfer_data_size(&c, DMA_SIZE_8);
    channel_config_set_ring(&c, true, ICE_USB_UART_RBBITS);
    channel_config_set_write_increment(&c, true);
    channel_config_set_read_increment(&c, false);
    channel_config_set_dreq(&c, uart_get_dreq(uart->inst, false));
    channel_config_set_chain_to(&c, chain_to);

    dma_channel_set_irq0_enabled(dma_chan, true);

    dma_channel_configure(
            dma_chan,
            &c,
            data,
            &uart_get_hw(uart->inst)->dr,
            count,
            false
    );
}

static void ice_usb_uart_rx_init(struct uart_wrap* uart) {
    char* wptrA = rb_write_ptr(&uart->rx_buf);
    char* wptrB = rb_write_ptr_next_ack(&uart->rx_buf, DMA_TCNT);
    ice_usb_uart_rx_conf_dma_chan(uart, uart->dma_chA, wptrA, DMA_TCNT, uart->dma_chB);
    ice_usb_uart_rx_conf_dma_chan(uart, uart->dma_chB, wptrB, DMA_TCNT, uart->dma_chA);

    hardware_alarm_set_callback(uart->dma_flush_alarm, uart->dma_flush_alarm_cb);
    hardware_alarm_set_target(uart->dma_flush_alarm, delayed_by_us(get_absolute_time(), DMA_ALARM_US));

    uart->dma_last_transfer = get_absolute_time();
    dma_channel_start(uart->dma_chA);
}

static void ice_usb_uart_rx_to_cdc(struct uart_wrap* uart) {
    while(1) {
        // this can be executed 2 times if the data is wrapped
        unsigned int bufsize = rb_data_left_continuous(&uart->rx_buf);

        if (bufsize == 0)
            break; // no data in buffer

        // returns how much data was actually written
        bufsize = tud_cdc_n_write(uart->itf, rb_read_ptr(&uart->rx_buf), bufsize);

        if (bufsize == 0)
            break; // cdc buffer full

        printf("%lu %4d\n", time_us_32(), bufsize);

        // ack data that was sent to cdc
        rb_read_ack(&uart->rx_buf, bufsize);
        // flush
        tud_cdc_n_write_flush(uart->itf);
    }
}


// ------------------------------- Tx functions -------------------------------
// cdc -> rb
//  rb -> uart

static void ice_usb_uart_tx_from_cdc(struct uart_wrap* uart) {
    while(1) {
        unsigned int bufsize = rb_space_left_continuous(&uart->tx_buf);
        if (bufsize == 0)
            break; // no buffer space left

        bufsize = tud_cdc_n_read(uart->itf, rb_write_ptr(&uart->tx_buf), bufsize);
        if (bufsize == 0)
            break; // cdc buffer empty

        rb_write_ack(&uart->tx_buf, bufsize);
    }
}

static void ice_usb_uart_tx(struct uart_wrap* uart) {
    while (1) {
        unsigned int bufsize = rb_data_left_continuous(&uart->tx_buf);
        if (bufsize == 0)
            break; // no data in buffer

        char* buf = rb_read_ptr(&uart->tx_buf);
        int wr;
        for (wr=0; wr<bufsize; wr++) {
            while (!uart_is_writable(uart->inst));
            uart_putc(uart->inst, *buf++);
        }

        rb_read_ack(&uart->tx_buf, wr);
    }
}


// ------------------------------- Debug functions -------------------------------

static void ice_usb_uart_debug(struct uart_wrap* wrap) {
    if (absolute_time_diff_us(wrap->dbg_time, get_absolute_time())/1000 > 100) {
        int rxdata = rb_data_left(&wrap->rx_buf)*100 / ICE_USB_UART_RBSIZE;
        int txdata = rb_data_left(&wrap->tx_buf)*100 / ICE_USB_UART_RBSIZE;

        if (rxdata > 0 || txdata > 0)
            printf("itf%d rx %4d%% tx %4d%%\n", wrap->itf, rxdata, txdata);

        wrap->dbg_time = get_absolute_time();
    }
}


// ------------------------------- Wrap functions -------------------------------

static void ice_usb_uart_wrap_init(struct uart_wrap* uart, char* rxcharbuf, char* txcharbuf) {
    rb_init(&uart->rx_buf, rxcharbuf, ICE_USB_UART_RBSIZE);
    rb_init(&uart->tx_buf, txcharbuf, ICE_USB_UART_RBSIZE);
    uart->dbg_time = get_absolute_time();
    uart->dma_chA = dma_claim_unused_channel(true);
    uart->dma_chB = dma_claim_unused_channel(true);
    uart->dma_flush_alarm = hardware_alarm_claim_unused(true);
    ice_usb_uart_rx_init(uart);
}

static void ice_usb_uart_wrap_task(struct uart_wrap* uart) {
    ice_usb_uart_debug(uart);
    ice_usb_uart_rx_to_cdc(uart);
    ice_usb_uart_tx(uart);
}


// ------------------------------- Wrap definitions -------------------------------

#ifdef ICE_USB_UART0_CDC
char uart0_rxcharbuf[ICE_USB_UART_RBSIZE] __aligned(ICE_USB_UART_RBSIZE);
char uart0_txcharbuf[ICE_USB_UART_RBSIZE] __aligned(ICE_USB_UART_RBSIZE);
void ice_usb_uart0_dma_flush_alarm();
struct uart_wrap uart0_wrap = {
        .itf = ICE_USB_UART0_CDC,
        .inst = uart0,
        .dma_flush_alarm_cb = ice_usb_uart0_dma_flush_alarm
};
void ice_usb_uart0_dma_flush_alarm() {
    ice_usb_uart_dma_flush_alarm(&uart0_wrap);
}
#endif

#ifdef ICE_USB_UART1_CDC
char uart1_rxcharbuf[ICE_USB_UART_RBSIZE] __aligned(ICE_USB_UART_RBSIZE);
char uart1_txcharbuf[ICE_USB_UART_RBSIZE] __aligned(ICE_USB_UART_RBSIZE);
void ice_usb_uart1_dma_flush_alarm();
struct uart_wrap uart1_wrap = {
        .itf = ICE_USB_UART1_CDC,
        .inst = uart1,
        .dma_flush_alarm_cb = ice_usb_uart1_dma_flush_alarm
};
void ice_usb_uart1_dma_flush_alarm() {
    ice_usb_uart_dma_flush_alarm(&uart1_wrap);
}
#endif


// ------------------------------- Baudrate setting -------------------------------

static void ice_usb_uart_set_baud(struct uart_wrap* uart, unsigned int baud) {
    uart_set_baudrate(uart->inst, baud);
}


// ------------------------------- DMA common IRQ 0 -------------------------------

static void ice_usb_uart_dma_irq0_common() {
#ifdef ICE_USB_UART0_CDC
    if (dma_channel_get_irq0_status(uart0_wrap.dma_chA)) {
        dma_channel_acknowledge_irq0(uart0_wrap.dma_chA);
        ice_usb_uart_rx_dma_irq0(&uart0_wrap, uart0_wrap.dma_chA);
    }
    if (dma_channel_get_irq0_status(uart0_wrap.dma_chB)) {
        dma_channel_acknowledge_irq0(uart0_wrap.dma_chB);
        ice_usb_uart_rx_dma_irq0(&uart0_wrap, uart0_wrap.dma_chB);
    }
#endif

#ifdef ICE_USB_UART1_CDC
    if (dma_channel_get_irq0_status(uart1_wrap.dma_chA)) {
        dma_channel_acknowledge_irq0(uart1_wrap.dma_chA);
        ice_usb_uart_rx_dma_irq0(&uart1_wrap, uart1_wrap.dma_chA);
    }
    if (dma_channel_get_irq0_status(uart1_wrap.dma_chB)) {
        dma_channel_acknowledge_irq0(uart1_wrap.dma_chB);
        ice_usb_uart_rx_dma_irq0(&uart1_wrap, uart1_wrap.dma_chB);
    }
#endif
}


// ------------------------------- Public init/task/cb -------------------------------

void ice_usb_uart_init() {
    irq_set_exclusive_handler(DMA_IRQ_0, ice_usb_uart_dma_irq0_common);
    irq_set_enabled(DMA_IRQ_0, true);

#ifdef ICE_USB_UART0_CDC
    ice_usb_uart_wrap_init(&uart0_wrap, uart0_rxcharbuf, uart0_txcharbuf);
#endif

#ifdef ICE_USB_UART1_CDC
    ice_usb_uart_wrap_init(&uart1_wrap, uart1_rxcharbuf, uart1_txcharbuf);
#endif
}

void ice_usb_uart_task() {
#ifdef ICE_USB_UART0_CDC
    ice_usb_uart_wrap_task(&uart0_wrap);
#endif

#ifdef ICE_USB_UART1_CDC
    ice_usb_uart_wrap_task(&uart1_wrap);
#endif
}

int ice_usb_uart_cb_baud(int itf, unsigned int baud) {
#ifdef ICE_USB_UART0_CDC
    if (itf == ICE_USB_UART0_CDC) {
        ice_usb_uart_set_baud(&uart0_wrap, baud);
        return 1;
    }
#endif
#ifdef ICE_USB_UART1_CDC
    if (itf == ICE_USB_UART1_CDC) {
        ice_usb_uart_set_baud(&uart1_wrap, baud);
        return 1;
    }
#endif
    return 0;
}

int ice_usb_uart_cb_rx(int itf) {
#ifdef ICE_USB_UART0_CDC
    if (itf == ICE_USB_UART0_CDC) {
        ice_usb_uart_tx_from_cdc(&uart0_wrap);
        return 1;
    }
#endif
#ifdef ICE_USB_UART1_CDC
    if (itf == ICE_USB_UART1_CDC) {
        ice_usb_uart_tx_from_cdc(&uart1_wrap);
        return 1;
    }
#endif
    return 0;
}

// TODO rx buffer heavily overflows, like 2000% usage, dma usage
// TODO first cdc transfer after boot fails, hmm

// UART
// TODO use dma