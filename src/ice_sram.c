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

// libc
#include <assert.h>

// pico-sdk
#include "hardware/gpio.h"
#include "hardware/spi.h"
#include "hardware/sync.h"
#include "pico/stdlib.h"

// pico-ice-sdk
#include "ice_sram.h"
#include "ice_spi.h"
#include "boards.h"

#define CMD_GET_ID              0x9F
#define CMD_GET_STATUS          0x05
#define CMD_RESET_ENABLE        0x66
#define CMD_RESET               0x99
#define CMD_READ                0x03
#define CMD_WRITE               0x02

void ice_sram_reset(const ice_spibus spibus) {
    const uint8_t command[] = { CMD_RESET_ENABLE, CMD_RESET };

    ice_spi_chip_select(spibus.CS_psram);
    ice_spi_write_blocking(command, sizeof(command));
    ice_spi_chip_deselect(spibus.CS_psram);
}

void ice_sram_init(const ice_spibus spibus) {
    ice_spi_init(spibus);
    ice_spi_init_cs_pin(spibus.CS_psram, true);

    // Device initialization procedure
    sleep_us(150);
    ice_sram_reset(spibus);
}

void ice_sram_get_id(const ice_spibus spibus, uint8_t id[8]) {
    const uint8_t command[] = { CMD_GET_ID, 0xFF, 0xFF, 0xFF };

    ice_spi_chip_select(spibus.CS_psram);
    ice_spi_write_blocking(command, sizeof(command));
    ice_spi_read_blocking(id, 8);
    ice_spi_chip_deselect(spibus.CS_psram);
}

void ice_sram_write_async(const ice_spibus spibus, uint32_t addr, const uint8_t *data, size_t data_size,
                          void (*callback)(volatile void *), void *context) {
    uint8_t command[] = { CMD_WRITE, addr >> 16, addr >> 8, addr };

    ice_spi_chip_select(spibus.CS_psram);
    ice_spi_write_blocking(command, sizeof(command));
    ice_spi_write_async(data, data_size, callback, context);
}

void ice_sram_write_blocking(const ice_spibus spibus, uint32_t addr, const uint8_t *data, size_t data_size) {
    while (data_size) {
        size_t transfer_size = ICE_SRAM_TRANSFER_SIZE;
        if (data_size < transfer_size) transfer_size = data_size;

        ice_sram_write_async(spibus, addr, data, transfer_size, NULL, NULL);
        ice_spi_wait_completion();
        ice_spi_chip_deselect(spibus.CS_psram);
        
        data_size -= transfer_size;
        data += transfer_size;
        addr += transfer_size;
    }
}

void ice_sram_read_async(const ice_spibus spibus, uint32_t addr, uint8_t *data, size_t data_size,
                          void (*callback)(volatile void *), void *context) {
    uint8_t command[] = { CMD_READ, addr >> 16, addr >> 8, addr };

    ice_spi_chip_select(spibus.CS_psram);
    ice_spi_write_blocking(command, sizeof(command));
    ice_spi_read_async(data, data_size, callback, context);
}

void ice_sram_read_blocking(const ice_spibus spibus, uint32_t addr, uint8_t *data, size_t data_size) {
    while (data_size) {
        size_t transfer_size = ICE_SRAM_TRANSFER_SIZE;
        if (data_size < transfer_size) transfer_size = data_size;

        ice_sram_read_async(spibus, addr, data, transfer_size, NULL, NULL);
        ice_spi_wait_completion();
        ice_spi_chip_deselect(spibus.CS_psram);
        
        data_size -= transfer_size;
        data += transfer_size;
        addr += transfer_size;
    }
}
