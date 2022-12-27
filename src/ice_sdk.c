#include "hardware/gpio.h"
#include "hardware/uart.h"
#include "hardware/spi.h"

#include "ice_sdk.h"
#include "ice_usb.h"
#include "ice_fpga.h"
#include "ice_fpga_flash.h"

void init_rgb_led(void) {
    gpio_init(ICE_LED_RED_PIN);
    gpio_init(ICE_LED_GREEN_PIN);
    gpio_init(ICE_LED_BLUE_PIN);
    gpio_set_dir(ICE_LED_RED_PIN, GPIO_OUT);
    gpio_set_dir(ICE_LED_GREEN_PIN, GPIO_OUT);
    gpio_set_dir(ICE_LED_BLUE_PIN, GPIO_OUT);
    gpio_put(ICE_LED_RED_PIN, false);
    gpio_put(ICE_LED_GREEN_PIN, true);
    gpio_put(ICE_LED_BLUE_PIN, true);
}

void ice_sdk_init(void) {
    //init_rgb_led(); //this can be called by the user. Otherwise interferes with FGPA executiong bitstream
    ice_usb_init();
    
    // Do not let the Pico control the FPGA flash so the FPGA is free to boot up
    ice_fpga_flash_deinit();

    ice_fpga_init();
    ice_fpga_reset(); //needed to allow FPGA to start execution
}
