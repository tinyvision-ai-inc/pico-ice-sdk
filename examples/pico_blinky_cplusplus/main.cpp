#include "pico/stdlib.h"
#include "boards/pico_ice.h"

// Deliberately adding all pico-ice-sdk headers here, even ones not needed for blinky, so that continuous integration
// verifies that all SDK headers can be compiled as C++.
#include "ice_cram.h"
#include "ice_flash.h"
#include "ice_fpga.h"
#include "ice_led.h"
#include "ice_pmod.h"
#include "ice_spi.h"
#include "ice_sram.h"
#include "ice_usb.h"
#include "ice_wishbone.h"

int main(void) {
    ice_led_init();

    for (bool red = false;; red = !red) {
        ice_led_red(red);
        sleep_ms(500);
    }
    return 0;
}
