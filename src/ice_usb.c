#include "hardware/gpio.h"
#include "hardware/uart.h"

#include "ice_usb.h"

// in src/tinyuf2/uf2.h
void uf2_init(void);

// in src/tinyuf2/board_api.h
void board_init(void);

/// Forward the data coming from USB CDC 1 UART to the FPGA UART.
/// Function to be called from tud_cdc_rx_cb().
void tud_cdc_rx_cb(uint8_t itf) {
    switch (itf) {
    case ICE_USB_UART_FPGA_ITF:
        while (tud_cdc_n_available(ICE_USB_UART_FPGA_ITF))
            uart_putc(uart_fpga, tud_cdc_n_read_char(ICE_USB_UART_FPGA_ITF));
        break;
    }
}

static void ice_fpga_uart_irq_handler(void) {
    while (uart_is_readable(uart_fpga)) {
        tud_cdc_n_write_char(1, uart_getc(uart_fpga));
        tud_cdc_n_write_flush(1);
    }
}

static void ice_fpga_init_uart(uint32_t baudrate_hz) {
    uart_init(uart_fpga, baudrate_hz);
    gpio_set_function(ICE_FPGA_UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(ICE_FPGA_UART_RX_PIN, GPIO_FUNC_UART);

    // For forwarding UART packets to USB.
    uart_set_irq_enables(uart_fpga, true, false);
    irq_set_enabled(ICE_FPGA_UART_IRQ, true);
    irq_set_exclusive_handler(ICE_FPGA_UART_IRQ, ice_fpga_uart_irq_handler);
}

void ice_usb_init(void) {
    // TinyUSB
    board_init();
    tusb_init();

    // TinyUF2
    uf2_init();

    // Enable the UART by default, allowing early init.
    ice_fpga_init_uart(115200);
}
