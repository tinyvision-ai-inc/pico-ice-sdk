#include "pico/stdlib.h"
#include "pico/stdio.h"

#include "boards/pico_ice.h"

#include "ice_fpga.h"
#include "ice_usb.h"

int main(void)
{
    // Enable USB-UART #0 output
    stdio_init_all();

    // Init the pico-ice-sdk library
    ice_usb_init();
    ice_fpga_init(48);
    ice_fpga_start();

    // Setup code here.
    for (;;) {
        tud_task();
    }
    return 0;
}
