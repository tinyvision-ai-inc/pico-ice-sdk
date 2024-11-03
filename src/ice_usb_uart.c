//
// Created by MrJake222 on 03/11/24.
//

#include "ice_usb_uart.h"

#include "rb.h"
#include "hardware/uart.h"
#include "hardware/irq.h"
#include "hardware/dma.h"

struct uart_wrap {
    int itf;            // CDC interface number
    uart_inst_t* inst;  // pico sdk instance reference

    int irq_num;
    void (*irq_handler)();

    struct rb rx_buf;
    struct rb tx_buf;

    absolute_time_t dbg_time;

    int dma_chA;
    int dma_chB;
};


// ------------------------------- Rx functions -------------------------------
// uart -> rb (irq)
//   rb -> cdc

#define DMA_T_LEN  16

enum dma_chan {
    DMA_CHAN_A,
    DMA_CHAN_B,
};

static void ice_usb_uart_rx_dma_irq0(struct uart_wrap* uart, enum dma_chan ch) {
    rb_write_ack(&uart->rx_buf, DMA_T_LEN);

    // complementary channel will write to write_ptr
    // need to skip another ack
    char* waddr = rb_write_ptr_next_ack(&uart->rx_buf, DMA_T_LEN);

    int channel = (ch == DMA_CHAN_A ? uart->dma_chA : uart->dma_chB);
    dma_channel_set_write_addr(channel, waddr, false);
}

static void ice_usb_uart_rx_conf_dma_chan(struct uart_wrap* uart, int dma_chan, char* data, uint count, int chain_to) {
    dma_channel_config c = dma_channel_get_default_config(dma_chan);
    channel_config_set_transfer_data_size(&c, DMA_SIZE_8);
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
    char* wptr = rb_write_ptr(&uart->rx_buf);
    ice_usb_uart_rx_conf_dma_chan(uart, uart->dma_chA, wptr,           DMA_T_LEN, uart->dma_chB);
    ice_usb_uart_rx_conf_dma_chan(uart, uart->dma_chB, wptr+DMA_T_LEN, DMA_T_LEN, uart->dma_chA);
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

        // ack data that was sent to cdc
        rb_read_ack(&uart->rx_buf, bufsize);
    }

    tud_cdc_n_write_flush(uart->itf);
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
        int rxdata = rb_data_left(&wrap->rx_buf)*100 / RB_BUFSIZE;
        int txdata = rb_data_left(&wrap->tx_buf)*100 / RB_BUFSIZE;

        if (rxdata > 0 || txdata > 0)
            printf("itf%d rx %4d%% tx %4d%%\n", wrap->itf, rxdata, txdata);

        wrap->dbg_time = get_absolute_time();
    }
}


// ------------------------------- Wrap functions -------------------------------

static void ice_usb_uart_wrap_init(struct uart_wrap* uart) {
    rb_init(&uart->rx_buf);
    rb_init(&uart->tx_buf);
    uart->dbg_time = get_absolute_time();
    uart->dma_chA = dma_claim_unused_channel(true);
    uart->dma_chB = dma_claim_unused_channel(true);
    ice_usb_uart_rx_init(uart);
}

static void ice_usb_uart_wrap_task(struct uart_wrap* uart) {
    ice_usb_uart_debug(uart);
    ice_usb_uart_rx_to_cdc(uart);
    ice_usb_uart_tx(uart);
}


// ------------------------------- Wrap definitions -------------------------------

#ifdef ICE_USB_UART0_CDC
struct uart_wrap uart0_wrap = {
        .itf = ICE_USB_UART0_CDC,
        .inst = uart0
};
#endif

#ifdef ICE_USB_UART1_CDC
struct uart_wrap uart1_wrap = {
        .itf = ICE_USB_UART1_CDC,
        .inst = uart1
};
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
        ice_usb_uart_rx_dma_irq0(&uart0_wrap, DMA_CHAN_A);
    }
    if (dma_channel_get_irq0_status(uart0_wrap.dma_chB)) {
        dma_channel_acknowledge_irq0(uart0_wrap.dma_chB);
        ice_usb_uart_rx_dma_irq0(&uart0_wrap, DMA_CHAN_B);
    }
#endif

#ifdef ICE_USB_UART1_CDC
    if (dma_channel_get_irq0_status(uart1_wrap.dma_chA)) {
        dma_channel_acknowledge_irq0(uart1_wrap.dma_chA);
        ice_usb_uart_rx_dma_irq0(&uart1_wrap, DMA_CHAN_A);
    }
    if (dma_channel_get_irq0_status(uart1_wrap.dma_chB)) {
        dma_channel_acknowledge_irq0(uart1_wrap.dma_chB);
        ice_usb_uart_rx_dma_irq0(&uart1_wrap, DMA_CHAN_B);
    }
#endif
}


// ------------------------------- Public init/task/cb -------------------------------

void ice_usb_uart_init() {
    irq_set_exclusive_handler(DMA_IRQ_0, ice_usb_uart_dma_irq0_common);
    irq_set_enabled(DMA_IRQ_0, true);

#ifdef ICE_USB_UART0_CDC
    ice_usb_uart_wrap_init(&uart0_wrap);
#endif

#ifdef ICE_USB_UART1_CDC
    ice_usb_uart_wrap_init(&uart1_wrap);
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