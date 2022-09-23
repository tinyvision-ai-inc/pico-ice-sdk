#include "pico_ice/fpga.h"
#include "hardware/clocks.h"
#include "hardware/uart.h"
#include "hardware/gpio.h"

/**
 * Initialise the FPGA clock at the given frequency.
 * @param mhz The clock speed in MHz. Valid values: 48MHz, 24MHz, 16MHz 12MHz, 8MHz, 6MHz, 4MHz, 3MHz, 2MHz, 1MHz.
 */
void fpga_init_clock(uint8_t mhz)
{
    clock_gpio_init(ICE_FPGA_CLOCK_PIN, CLOCKS_CLK_GPOUT0_CTRL_AUXSRC_VALUE_CLK_USB, 48 / mhz);
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
}
