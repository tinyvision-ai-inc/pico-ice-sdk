#include "pico/stdlib.h"
#include "pico/stdio.h"
#include "boards/pico_ice.h"
#include "ice_cram.h"
#include "ice_fpga.h"
#include "ice_led.h"
#include "ice_spi.h"
#include "rgb_blink.h"

int main(void) {
    ice_led_init();
    ice_spi_init();
    ice_fpga_init(48);

    ice_cram_open();
    ice_cram_write(rgb_blink, sizeof(rgb_blink));
    ice_cram_close();

    ice_fpga_start();

    while (1);
    return 0;
}
