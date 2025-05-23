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

#include <stdio.h>
#include "pico/stdlib.h"
#include "boards.h"
#include "ice_flash.h"

#define MY_BASE_ADDRESS 0x00000

static inline void memdump(uint8_t const *buf, size_t sz) {
    for (size_t i = 0; i < sz; i++) {
        printf(" %02X", buf[i]);
        if (i % 0x20 == (0x20 - 1)) {
            printf("\r\n");
        }
    }
    printf("\r\n");
}

#include "ice_led.h" // TODO debug

int main(void) {
    uint8_t buf_r[ICE_FLASH_PAGE_SIZE] = {0};
    uint8_t buf_w[ICE_FLASH_PAGE_SIZE] = {0};

    // Enable USB-UART 0 output
    stdio_init_all();

    sleep_ms(2000);

    // Booted up, now take control of the Flash
    ice_flash_init(FPGA_DATA.bus, ICE_FLASH_BAUDRATE);

    // Write data: known pattern, not very random!
    for (size_t i = 0; i < sizeof buf_w; i++) {
        buf_w[i] = i;
    }

    for (uint16_t i = 0;; i++) {
        // Erase a sector, program the page and then read it back.
        // Note that the FPGA bitfile which is at 0x000000
        ice_flash_erase_sector(FPGA_DATA.bus, MY_BASE_ADDRESS);
        ice_flash_read(FPGA_DATA.bus, MY_BASE_ADDRESS, buf_r, sizeof buf_r);
        memdump(buf_r, sizeof buf_r);
        ice_flash_program_page(FPGA_DATA.bus, MY_BASE_ADDRESS, buf_w);
        ice_flash_read(FPGA_DATA.bus, MY_BASE_ADDRESS, buf_r, sizeof buf_r);
        memdump(buf_r, sizeof buf_r);

        sleep_ms(5000);
    }

    return 0;
}
