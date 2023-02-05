#include "pico/stdlib.h"
#include "pico/stdio.h"

#include "hardware/dma.h"
#include "hardware/gpio.h"
#include "hardware/spi.h"

#include "boards/pico_ice.h"

#include "ice_usb.h"
#include "ice_sdk.h"
#include "ice_fpga.h"
#include "ice_comm.h"

#define DATA_LEN 8
#define START_ADDR 0xdead

int main() {
    ice_sdk_init();
    stdio_init_all();

    ice_init();
    ice_comm_init();

    // Dont steal the RGB LED pins from the FPGA
    gpio_set_dir(ICE_LED_RED_PIN, GPIO_IN);
    gpio_set_dir(ICE_LED_GREEN_PIN, GPIO_IN);
    gpio_set_dir(ICE_LED_BLUE_PIN, GPIO_IN);

    ice_init_clock(12); // Setup the clock to the FPGA
    ice_reset(); // Issue a good reset to the FPGA, check if it came up

    while (1)
    {
        tud_task();
    }
    
/*
    // Example of writing/reading the FPGA SPI port:
    uint8_t write_data[DATA_LEN];
    uint8_t read_data[DATA_LEN];
    for (uint16_t i = 0; i < DATA_LEN; i++) {
        write_data[i] = i;
    }

    for (;;) {
        tud_task();
        ice_comm_write(START_ADDR, write_data, sizeof(write_data));
        ice_comm_read(read_data, START_ADDR, sizeof(read_data));
    }
*/
}
