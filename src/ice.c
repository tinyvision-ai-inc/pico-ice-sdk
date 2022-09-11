#include <assert.h>
#include "pico-ice/ice.h"

static int ice_flash_init_done;

void
ice_flash_init(void)
{
    // Init the SPI dedicated to flashing the FPGA
    spi_init(spi_flash, 1000 * 1000);

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
ice_flash_erase(void)
{
    assert(ice_flash_init_done);
    flash_erase_chip(spi_flash, ICE_FLASH_SPI_CSN_PIN);
}
