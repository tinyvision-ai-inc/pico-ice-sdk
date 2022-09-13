#include "hardware/clocks.h"
#include "pico_ice/fpga.h"

void
fpga_init_clock(uint8_t mhz)
{
    clock_gpio_init(ICE_FPGA_CLOCK_PIN, CLOCKS_CLK_GPOUT0_CTRL_AUXSRC_VALUE_CLK_USB, 48 / mhz);
}
