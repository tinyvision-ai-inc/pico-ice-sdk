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
#include "tusb.h"
#include "boards/pico_ice.h"
#include "ice_spi.h"
#include "ice_flash.h"

#define MY_BASE_ADDRESS 0x00000

static inline void memdump(uint8_t const *buf, size_t sz) {
    for (size_t i = 0; i < sz; i++) {
        printf(" %02X", buf[i]);
        if (i % 0x40 == (0x40 - 1)) {
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

    ice_led_init();

    // Booted up, now take control of the Flash
    ice_spi_init(1000000);
    ice_flash_init();

    // Write data: known pattern, not very random!
    for (size_t i = 0; i < sizeof buf_w; i++) {
        buf_w[i] = i;
    }

    for (uint16_t i = 0;; i++) {
        tud_task(); 

        // Erase a sector, program the page and then read it back.
        // Note that we're using MY_BASE_ADDRESS to avoid erasing the FPGA bitfile which is at 0x0
        ice_flash_erase_sector(MY_BASE_ADDRESS);
        ice_flash_program_page(MY_BASE_ADDRESS, buf_w);
        ice_flash_read(MY_BASE_ADDRESS, buf_r, sizeof buf_r);
        memdump(buf_r, sizeof buf_r);

        ice_led_red(true);

        sleep_ms(10000);
    }

    return 0;
}
