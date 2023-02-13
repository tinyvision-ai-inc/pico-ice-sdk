#include "pico/stdlib.h"
#include "pico/stdio.h"

#include "boards/pico_ice.h"

#include "ice_fpga.h"
#include "ice_flash.h"
#include "ice_usb.h"
#include "ice_led.h"
#include "ice_spi.h"
#include "tinyuf2/board_api.h"

int main(void) {
    // Init USB
    stdio_init_all();
    board_init();
    tusb_init();

    // Init LEDs
    ice_led_init();

    // Init FPGA
    ice_spi_release_bus();
    ice_fpga_init(48);
    ice_fpga_start();
    ice_spi_init();

    // Run USB task
    for (bool sck;;) {
        tud_task();
    }

    return 0;
}
