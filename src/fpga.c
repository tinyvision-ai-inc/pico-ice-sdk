#include "hardware/clocks.h"
#include "hardware/uart.h"
#include "hardware/gpio.h"
#include "pico_ice/fpga.h"

void
fpga_init_clock(uint8_t mhz)
{
    clock_gpio_init(ICE_FPGA_CLOCK_PIN, CLOCKS_CLK_GPOUT0_CTRL_AUXSRC_VALUE_CLK_USB, 48 / mhz);
}

void
fpga_init_uart(uint32_t mhz)
{
    uart_init(uart_fpga, mhz);
    gpio_set_function(ICE_FPGA_UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(ICE_FPGA_UART_RX_PIN, GPIO_FUNC_UART);
}
