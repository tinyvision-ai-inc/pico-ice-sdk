#include "pico/stdlib.h"
#include "pico/stdio.h"
#include "boards/pico_ice.h"
#include "ice/usb.h"
#include "hardware/dma.h"
#include "hardware/gpio.h"
#include "hardware/spi.h"
#include "ice/init.h"
#include "ice/fpga.h"
#include "ice/fpga_comm.h"

#define DATA_LEN 8
#define START_ADDR 0xdead

int main() {
    stdio_init_all();
    ice_sdk_init();

    ice_fpga_reset();
    init_fpga_comm_spi_dma_interface();

    uint8_t write_data[DATA_LEN];
    uint8_t read_data[DATA_LEN];
    for (uint16_t i = 0; i < DATA_LEN; i++)
        write_data[i] = i;

    for (;;) {
        ice_usb_task();
        ice_write_fpga_spi_dma(START_ADDR, write_data, sizeof(write_data));
        ice_read_fpga_spi_dma(read_data, START_ADDR, sizeof(read_data));
    }
}
