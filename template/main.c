#include "pico/stdlib.h"
#include "pico/stdio.h"
#include "boards/pico_ice.h"
#include "ice_usb.h"
#include "ice_fpga.h"
#include "ice_led.h"

int main(void) {
    stdio_init_all();
    tusb_init();

    // Release the LED bus
    ice_led_init();

    // Let the FPGA start and give it a clock
    ice_fpga_init(48);
    ice_fpga_start();

    // [...] more setup code here

    for (;;) {
        tud_task();

        // [...] more application code here
    }
    return 0;
}
