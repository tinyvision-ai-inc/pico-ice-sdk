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
#include "boards.h"
#include "ice_fpga.h"
#include "ice_spi.h"
#include "ice_led.h"
#include "tusb.h"

#define DATA_LEN 8
#define START_ADDR 0xdead

int main(void) {
    tusb_init();
    ice_led_init();
    ice_fpga_init(12);
    ice_fpga_start();

    for (uint8_t i = 0;; i++) {
        uint8_t buffer[] = { i };

        tud_task();
        ice_fpga_write(0x55551001, buffer, sizeof buffer);
        ice_fpga_read(0x55551001, buffer, sizeof buffer);
    }
}
