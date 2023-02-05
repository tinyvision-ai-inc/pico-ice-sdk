#include "pico/stdlib.h"
#include "pico/stdio.h"
#include "boards/pico_ice.h"

// Deliberately adding all pico-ice-sdk headers here, even ones not needed for blinky, so that continuous integration
// verifies that all SDK headers can be compiled as C++.
#include "ice_flash.h"
#include "ice_fpga.h"
#include "ice_comm.h"
#include "ice_sdk.h"
#include "ice_smem.h"
#include "ice_usb.h"

int main() {
    gpio_init(ICE_LED_RED_PIN);
    gpio_put(ICE_LED_RED_PIN, true); // active-low
    gpio_set_dir(ICE_LED_RED_PIN, GPIO_OUT);

    for (;;) {
        gpio_put(ICE_LED_RED_PIN, false);
        sleep_ms(500);
        gpio_put(ICE_LED_RED_PIN, true);
        sleep_ms(500);
    }
    return 0;
}
