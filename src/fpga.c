#include "pico_ice/fpga.h"
#include "hardware/clocks.h"
#include "hardware/uart.h"
#include "hardware/gpio.h"
#include "tusb.h"

/**
 * Initialise the FPGA clock at the given frequency.
 * @param mhz The clock speed in MHz. Valid values: 48MHz, 24MHz, 16MHz 12MHz, 8MHz, 6MHz, 4MHz, 3MHz, 2MHz, 1MHz.
 */
void fpga_init_clock(uint8_t mhz)
{
    clock_gpio_init(ICE_FPGA_CLOCK_PIN, CLOCKS_CLK_GPOUT0_CTRL_AUXSRC_VALUE_CLK_USB, 48 / mhz);
}

/**
 * Interrupt handler for reception of data from the UART instance connected to the FPGA.
 */
static void fpga_uart_irq_handler(void)
{
    while (uart_is_readable(uart_fpga)) {
        tud_cdc_n_write_char(1, uart_getc(uart_fpga));
        tud_cdc_n_write_flush(1);
    }
}

/**
 * @brief Initialise the UART peripheral for communication with the FPGA, at the given baudrate.
 * @param mhz The baud rate speed in MHz. Can be any value supported by the pico-sdk.
 */
void fpga_init_uart(uint32_t mhz)
{
    uart_init(uart_fpga, mhz);
    gpio_set_function(ICE_FPGA_UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(ICE_FPGA_UART_RX_PIN, GPIO_FUNC_UART);

    // For forwarding UART packets to USB.
    uart_set_irq_enables(uart_fpga, true, false);
    irq_set_enabled(ICE_FPGA_UART_IRQ, true);
    irq_set_exclusive_handler(ICE_FPGA_UART_IRQ, fpga_uart_irq_handler);
}
