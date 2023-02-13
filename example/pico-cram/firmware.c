#include "pico/stdlib.h"
#include "pico/stdio.h"

#include "boards/pico_ice.h"

#include "ice_cram.h"

int main(void) {
    uint8_t bitstream[3] = {1, 2, 3};

    ice_fpga_init(48);

    ice_cram_open();
    ice_cram_write(bitstream, sizeof(bitstream));
    ice_cram_close();

    ice_fpga_start(48);

    while (1);
    return 0;
}
