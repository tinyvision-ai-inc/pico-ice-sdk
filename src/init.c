#include "ice/init.h"
#include "ice/usb.h"
#include "ice/flash.h"
#include "ice/fpga.h"
#include "hardware/gpio.h"
#include "hardware/uart.h"
#include "hardware/spi.h"

/**
 * Call all functions below with default values.
 * No need to call any other initialization function when this is called.
 */
void ice_init(void)
{
    ice_flash_init();
    ice_usb_init();
    ice_fpga_init();
}
