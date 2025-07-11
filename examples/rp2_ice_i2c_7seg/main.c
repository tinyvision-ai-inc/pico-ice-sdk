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
#include "hardware/i2c.h"
#include "hardware/spi.h"
#include "boards.h"
#include "ice_cram.h"
#include "ice_fpga.h"
#include "ice_led.h"

#include <stdio.h>

#define APP_I2C i2c0
#define APP_I2C_SDA_PIN 28
#define APP_I2C_SCL_PIN 29

uint8_t bitstream[] = {
#include "bitstream.h"
};

int main(void) {
    int ret;

    // For console REPL
    stdio_init_all();

    // For debug purpose with i.e. ice_led_red(true);
    ice_led_init();

    // Initialize the FPGA
    ice_fpga_init(FPGA_DATA, 24);
    ice_fpga_start(FPGA_DATA);

    // Write the whole bitstream to the FPGA CRAM
    ice_cram_open(FPGA_DATA);
    ice_cram_write(bitstream, sizeof(bitstream));
    ice_cram_close();

    // Initialize the I2C bus
    i2c_init(APP_I2C, 48000);
    gpio_set_function(APP_I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(APP_I2C_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(APP_I2C_SDA_PIN);
    gpio_pull_up(APP_I2C_SCL_PIN);

    // Run test I2C commands for the sake of testing the FPGA communication over I2C
    for (uint8_t tx = 0;; tx++) {
        uint8_t buf[1] = {tx};
        printf("i2c scan:");

        for (int i = 0; i < 0x7f; i++) {
            ret = i2c_write_blocking(APP_I2C, i, buf, sizeof(buf), false);
            if (ret >= 0) {
                printf(" 0x%02x", i);
            }

            sleep_us(100);
        }
        printf("\n");

        sleep_us(500);
    }

    return 0;
}
