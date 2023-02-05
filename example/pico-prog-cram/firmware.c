#include "pico/stdlib.h"
#include "pico/stdio.h"

#include "boards/pico_ice.h"

#include "ice_sdk.h"
#include "ice_usb.h"
#include "ice_bitstream.h"

// This is a hack for testing. ice_bitstream should have its own example.
int main(void) {
    // Init the pico-ice-sdk library
    ice_sdk_init();

    // Enable USB-UART #0 output
    stdio_init_all();

    uint8_t bitstream[3] = {1, 2, 3};
    ice_bitstream_open();
    ice_bitstream_write(bitstream, sizeof(bitstream));
    ice_bitstream_close();

    // Setup code here.
    for (;;) {
        tud_task();
        printf("hello world\r\n");

    }
    return 0;
}
