#include "hardware/gpio.h"
#include "hardware/uart.h"
#include "hardware/spi.h"
#include "pico_ice/ice.h"
#include "pico_ice/priv.h"
#include "pico_ice/flash.h"
#include "pico_ice/fpga.h"

void
ice_init_defaults(void)
{
    ice_init_flash();
    ice_init_usb();
    ice_init_fpga();
}

void
ice_init_flash(void)
{
    // Init the SPI dedicated to flashing the FPGA
    spi_init(spi_fpga_flash, 10 * 1000 * 1000);

    // Setup the associated GPIO pins except CSN
    gpio_set_function(ICE_FLASH_SPI_SCK_PIN, GPIO_FUNC_SPI);
    gpio_set_function(ICE_FLASH_SPI_TX_PIN, GPIO_FUNC_SPI);
    gpio_set_function(ICE_FLASH_SPI_RX_PIN, GPIO_FUNC_SPI);

    // Setup the CSN pin to GPIO mode for manual control
    gpio_init(ICE_FLASH_SPI_CSN_PIN);
    gpio_set_dir(ICE_FLASH_SPI_CSN_PIN, GPIO_OUT);
    gpio_put(ICE_FLASH_SPI_CSN_PIN, 1);
}

void
ice_init_usb(void)
{
    // TinyUSB
    board_init();
    tusb_init();

    // TinyUF2
    uf2_init();
}

void
ice_init_fpga(void)
{
    fpga_init_clock(48);
    fpga_init_uart(115200);
}

void
ice_usb_task(void)
{
    tud_task();
    tud_task_cdc();
}
