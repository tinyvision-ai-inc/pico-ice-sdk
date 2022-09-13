#include <assert.h>
#include "hardware/gpio.h"
#include "hardware/spi.h"
#include "hardware/clocks.h"
#include "pico_ice/ice.h"
#include "pico_ice/flash.h"

static int ice_flash_init_done;

void
ice_init_flash(void)
{
    // Init the SPI dedicated to flashing the FPGA
    spi_init(spi_fpga_flash, 1000 * 1000);

    // Setup the associated GPIO pins except CSN
    gpio_set_function(ICE_FLASH_SPI_SCK_PIN, GPIO_FUNC_SPI);
    gpio_set_function(ICE_FLASH_SPI_TX_PIN, GPIO_FUNC_SPI);
    gpio_set_function(ICE_FLASH_SPI_RX_PIN, GPIO_FUNC_SPI);

    // Setup the CSN pin to GPIO mode for manual control
    gpio_init(ICE_FLASH_SPI_CSN_PIN);
    gpio_set_dir(ICE_FLASH_SPI_CSN_PIN, GPIO_OUT);
    gpio_put(ICE_FLASH_SPI_CSN_PIN, 1);

    // For assert()s below
    ice_flash_init_done = 1;
}

void
ice_init_fpga_clock(uint8_t mhz)
{
	clock_gpio_init(ICE_FPGA_CLOCK_PIN, CLOCKS_CLK_GPOUT0_CTRL_AUXSRC_VALUE_CLK_USB, 48 / mhz);
}
