/*
 * MIT License
 *
 * Copyright (c) 2023 tinyVision.ai
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "pico/stdlib.h"
#include "pico/stdio.h"
#include "hardware/dma.h"
#include "hardware/gpio.h"
#include "hardware/spi.h"
#include "boards/pico_ice.h"
#include "ice_fpga.h"
#include "ice_spi.h"
#include "ice_led.h"
#include "ice_comm.h"

#define DATA_LEN 8
#define START_ADDR 0xdead

int main(void) {
    ice_led_init();
    ice_fpga_init(48);
    ice_fpga_start();

    ice_comm_init();

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
}
