#include "hardware/gpio.h"
#include "hardware/uart.h"
#include "hardware/watchdog.h"
#include "ice_usb.h"

// in src/tinyuf2/uf2.h
void uf2_init(void);

// in src/tinyuf2/board_api.h
void board_init(void);

static void ice_uart_irq_handler(void)
{
    while (uart_is_readable(uart_fpga)) {
        tud_cdc_n_write_char(1, uart_getc(uart_fpga));
        tud_cdc_n_write_flush(1);
    }
}

void ice_usb_init(void)
{
    // TinyUSB
    board_init();
    tusb_init();

    // TinyUF2
    uf2_init();

    // Enable the UART by default, allowing early init.
    uart_init(uart_fpga, 115200);
    gpio_set_function(ICE_FPGA_UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(ICE_FPGA_UART_RX_PIN, GPIO_FUNC_UART);

    // For forwarding UART packets to USB.
    uart_set_irq_enables(uart_fpga, true, false);
    irq_set_enabled(ICE_FPGA_UART_IRQ, true);
    irq_set_exclusive_handler(ICE_FPGA_UART_IRQ, ice_uart_irq_handler);
}
