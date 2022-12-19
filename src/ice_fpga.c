#include "hardware/clocks.h"
#include "hardware/gpio.h"
#include "hardware/uart.h"
#include "pico/stdlib.h"
#include "tusb.h"

#include "ice_fpga.h"
#include "ice_fpga_flash.h"

void ice_fpga_init(void) {
    // Keep the FPGA in reset until ice_fpga_reset() is called.
    gpio_put(ICE_FPGA_CRESET_PIN, false);
    gpio_init(ICE_FPGA_CRESET_PIN);
    gpio_set_dir(ICE_FPGA_CRESET_PIN, GPIO_OUT);

    // Input pin for sensing configuration status.
    gpio_init(ICE_FPGA_CDONE_PIN);
    gpio_set_dir(ICE_FPGA_CDONE_PIN, GPIO_IN);

    // Output a clock by default.
    ice_fpga_init_clock(48);

    // Enable the UART by default, allowing early init.
    ice_fpga_init_uart(115200);
}

void ice_fpga_halt(void) {
    gpio_put(ICE_FPGA_CRESET_PIN, false);
}

bool ice_fpga_reset(void) {
    // Issue a reset pulse.
    gpio_put(ICE_FPGA_CRESET_PIN, false);
    sleep_ms(1);
    gpio_put(ICE_FPGA_CRESET_PIN, true);

    // Wait that the configuration is finished before interferring.
    // This makes sure the SPI bus is not driven by both the FPGA
    // (reading from flash) and the RP2040 (configuring the flash).
    // Note that if the flash is corrupted, this function will timeout!
    for (uint8_t timeout = 100; !gpio_get(ICE_FPGA_CDONE_PIN); timeout--) {
        if (timeout == 0)
            return false;
        sleep_ms(1);
    }
    return true;
}

void ice_fpga_init_clock(uint8_t freq_mhz) {
    clock_gpio_init(ICE_FPGA_CLOCK_PIN, CLOCKS_CLK_GPOUT0_CTRL_AUXSRC_VALUE_CLK_USB, 48 / freq_mhz);
}

static void ice_fpga_uart_irq_handler(void) {
    while (uart_is_readable(uart_fpga)) {
        tud_cdc_n_write_char(1, uart_getc(uart_fpga));
        tud_cdc_n_write_flush(1);
    }
}

void ice_fpga_init_uart(uint32_t baudrate_hz) {
    uart_init(uart_fpga, baudrate_hz);
    gpio_set_function(ICE_FPGA_UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(ICE_FPGA_UART_RX_PIN, GPIO_FUNC_UART);

    // For forwarding UART packets to USB.
    uart_set_irq_enables(uart_fpga, true, false);
    irq_set_enabled(ICE_FPGA_UART_IRQ, true);
    irq_set_exclusive_handler(ICE_FPGA_UART_IRQ, ice_fpga_uart_irq_handler);
}
