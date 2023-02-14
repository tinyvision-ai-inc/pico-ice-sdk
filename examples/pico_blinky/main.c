#include "pico/stdlib.h"
#include "boards/pico_ice.h"
#include "ice_led.h"

int main(void) {
    ice_led_init();

    // Note that the FPGA demo might as well making use of the LED.
    // In that case, the LED "on" state win over the "off" state,
    // but LEDs work fine nonetheless.

    for (bool red = false;; red = !red) {
        ice_led_red(red);
        sleep_ms(500);
    }
    return 0;
}
