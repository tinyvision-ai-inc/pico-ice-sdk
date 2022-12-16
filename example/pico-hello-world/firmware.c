#include "pico/stdlib.h"
#include "pico/stdio.h"
#include "boards/pico_ice.h"
#include "ice/sdk.h"
#include "ice/usb.h"

int main(void) {
    // Init the pico-ice-sdk library
    ice_sdk_init();

    // Enable USB-UART #0 output
    stdio_init_all();

    // Setup code here.
    for (;;) {
        tud_task();
        printf("hello world\r\n");
    }
    return 0;
}
