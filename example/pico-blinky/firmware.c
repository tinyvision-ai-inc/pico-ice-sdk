#include "pico/stdlib.h"
#include "ice_led.h"

int main(void)
{
    ice_led_init();

    // Note that the FPGA demo might as well making use of the LED.
    // In that case, the LED "on" state win over the "off" state,
    // but LEDs work fine nontheless.

    for (;;) {
        ice_led_red(true); // led bright
        sleep_ms(500);
        ice_led_red(false); // led off
        sleep_ms(500);
    }
    return 0;
}
