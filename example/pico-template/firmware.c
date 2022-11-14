#include "pico/stdlib.h"
#include "pico/stdio.h"
#include "boards/pico_ice.h"
#include "pico_ice/ice.h"

int
main(void)
{
    stdio_init_all();
    ice_init();

    // Setup code here.

    for (;;) {
        ice_usb();

        // Application code here.

    }
    return 0;
}
