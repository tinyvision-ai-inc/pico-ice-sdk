#include "pico/stdlib.h"
#include "pico/stdio.h"
#include "boards/pico_ice.h"
#include "ice/init.h"
#include "ice/usb.h"

int
main(void)
{
    stdio_init_all();
    ice_init();

    // Setup code here.

    for (;;) {
        ice_usb_task();

        // Application code here.

    }
    return 0;
}
