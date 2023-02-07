#include "hardware/clocks.h"
#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include "ice_fpga.h"

void ice_fpga_init(uint8_t freq_mhz)
{
    // This keeps the FPGA in reset until ice_fpga_start() is called.
    gpio_put(ICE_FPGA_CRESET_PIN, false);
    gpio_init(ICE_FPGA_CRESET_PIN);
    gpio_set_dir(ICE_FPGA_CRESET_PIN, GPIO_OUT);

    // Input pin for sensing configuration status.
    gpio_init(ICE_FPGA_CDONE_PIN);
    gpio_set_dir(ICE_FPGA_CDONE_PIN, GPIO_IN);

    // Output a clock by default.
    clock_gpio_init(ICE_FPGA_CLOCK_PIN, CLOCKS_CLK_GPOUT0_CTRL_AUXSRC_VALUE_CLK_USB, 48 / freq_mhz);
}

void ice_fpga_halt(void)
{
    gpio_put(ICE_FPGA_CRESET_PIN, false);
}

bool ice_fpga_start(void)
{
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
