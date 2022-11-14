#include "pico/stdlib.h"
#include "pico/stdio.h"
#include "boards/pico_ice.h"

int
main(void)
{
    gpio_init(ICE_LED_RED_PIN);
    gpio_put(ICE_LED_RED_PIN, true); // active-low
    gpio_set_dir(ICE_LED_RED_PIN, GPIO_OUT);

    for (;;) {
        gpio_put(ICE_LED_RED_PIN, false);
        sleep_ms(1000);
        gpio_put(ICE_LED_RED_PIN, true);
        sleep_ms(1000);
    }
    return 0;
}
