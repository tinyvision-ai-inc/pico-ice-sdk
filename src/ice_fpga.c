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

// pico-sdk
#include "hardware/clocks.h"
#include "hardware/gpio.h"
#include "pico/stdlib.h"

// pico-ice-sdk
#include "boards.h"
#include "ice_fpga.h"
#include "ice_spi.h"

void ice_fpga_init(uint8_t freq_mhz) {
    uint src = CLOCKS_CLK_GPOUT0_CTRL_AUXSRC_VALUE_CLK_USB;

    clock_gpio_init(ICE_FPGA_CLOCK_PIN, src, 48 / freq_mhz);

    ice_spi_init();
    ice_spi_init_cs_pin(ICE_FPGA_CSN_PIN, false);
}

void ice_fpga_stop(void) {
    gpio_init(ICE_FPGA_CRESET_B_PIN);
    gpio_put(ICE_FPGA_CRESET_B_PIN, false);
    gpio_set_dir(ICE_FPGA_CRESET_B_PIN, GPIO_OUT);
}

// Datasheet iCE40 Programming Configuration - 3.1. Mode Selection
bool ice_fpga_start(void) {
    // For sensing configuration status.
    gpio_init(ICE_FPGA_CDONE_PIN);

    // To take the FPGA out of reset
    gpio_init(ICE_FPGA_CRESET_B_PIN);
    gpio_put(ICE_FPGA_CRESET_B_PIN, true);
    gpio_set_dir(ICE_FPGA_CRESET_B_PIN, GPIO_OUT);

    // Wait that the configuration is finished before interferring.
    // This makes sure the SPI bus is not driven by both the FPGA
    // (reading from flash) and the RP2040 (configuring the flash).
    // Note that if the flash is corrupted, this function will timeout!
    for (uint8_t timeout = 100; !gpio_get(ICE_FPGA_CDONE_PIN); timeout--) {
        if (timeout == 0) {
            // if the FPGA could not start, it would keep the clock active,
            // which disturpts the rest of the signals, including SWD
            ice_fpga_stop();
            return false;
        }
        sleep_ms(1);
    }
    return true;
}
