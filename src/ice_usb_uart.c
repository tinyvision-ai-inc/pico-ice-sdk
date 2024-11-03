//
// Created by MrJake222 on 03/11/24.
//

#include "ice_usb_uart.h"

#include "rb.h"
#include "hardware/uart.h"
#include "hardware/irq.h"

struct uart_wrap {
    int itf;            // CDC interface number
    uart_inst_t* inst;  // pico sdk instance reference

    int irq_num;
    void (*irq_handler)();

    struct rb rx_buf;
    struct rb tx_buf;

    absolute_time_t dbg_time;
};


// ------------------------------- Rx functions -------------------------------
// uart -> rb (irq)
//   rb -> cdc

static void ice_usb_uart_rx_irq(struct uart_wrap* uart)
{
    while (uart_is_readable(uart->inst)) {
        uint8_t byte = uart_getc(uart->inst);
        *rb_write_ptr(&uart->rx_buf) = byte;
        rb_write_ack(&uart->rx_buf, 1);
    }
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
    irq_set_exclusive_handler(uart->irq_num, uart->irq_handler);
    irq_set_enabled(uart->irq_num, true);
    uart_set_irq_enables(uart->inst, true, false);
}

static void ice_usb_uart_wrap_task(struct uart_wrap* uart) {
    ice_usb_uart_debug(uart);
    ice_usb_uart_rx_to_cdc(uart);
    ice_usb_uart_tx(uart);
}


// ------------------------------- Wrap definitions -------------------------------

#ifdef ICE_USB_UART0_CDC
void ice_usb_uart0_rx_irq();
struct uart_wrap uart0_wrap = {
        .itf = ICE_USB_UART0_CDC,
        .inst = uart0,
        .irq_num = UART0_IRQ,
        .irq_handler = ice_usb_uart0_rx_irq,
        .rx_buf = { 0 },
        .tx_buf = { 0 },
        .dbg_time = 0
};
void ice_usb_uart0_rx_irq() {
    ice_usb_uart_rx_irq(&uart0_wrap);
}
#endif

#ifdef ICE_USB_UART1_CDC
void ice_usb_uart1_rx_irq();
struct uart_wrap uart1_wrap = {
        .itf = ICE_USB_UART1_CDC,
        .inst = uart1,
        .irq_num = UART1_IRQ,
        .irq_handler = ice_usb_uart1_rx_irq,
        .rx_buf = { 0 },
        .tx_buf = { 0 },
        .dbg_time = 0
};
void ice_usb_uart1_rx_irq() {
    ice_usb_uart_rx_irq(&uart1_wrap);
}
#endif


// ------------------------------- Baudrate setting -------------------------------

static void ice_usb_uart_set_baud(struct uart_wrap* uart, unsigned int baud) {
    uart_set_baudrate(uart->inst, baud);
}

// ------------------------------- Public init/task/cb -------------------------------

void ice_usb_uart_init() {
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