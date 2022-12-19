#include "pico/stdlib.h"
#include "pico/stdio.h"

#include "hardware/dma.h"
#include "hardware/gpio.h"
#include "hardware/spi.h"

#include "boards/pico_ice.h"

#include "ice_usb.h"
#include "ice_sdk.h"
#include "ice_fpga.h"
#include "ice_fpga_comm.h"

#define DATA_LEN 8
#define START_ADDR 0xdead

int main() {
    ice_sdk_init();
    stdio_init_all();

    ice_fpga_reset();
    ice_fpga_comm_init();

    uint8_t write_data[DATA_LEN];
    uint8_t read_data[DATA_LEN];
    for (uint16_t i = 0; i < DATA_LEN; i++) {
        write_data[i] = i;
    }

    for (;;) {
        tud_task();
        ice_fpga_comm_write(START_ADDR, write_data, sizeof(write_data));
        ice_fpga_comm_read(read_data, START_ADDR, sizeof(read_data));
    }
}
