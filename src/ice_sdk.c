#include "hardware/gpio.h"
#include "hardware/uart.h"
#include "hardware/spi.h"

#include "ice_sdk.h"
#include "ice_usb.h"
#include "ice_fpga.h"
#include "ice_flash.h"

void ice_sdk_init(void) {
    init_rgb_led();
    ice_usb_init();
    
    // Do not let the Pico control the FPGA flash so the FPGA is free to boot up
    ice_flash_deinit();

    ice_init();
}
