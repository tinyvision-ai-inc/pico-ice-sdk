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
#include "boards/pico_ice.h"

// pico-ice-sdk
#include "ice_sram.h"
#include "ice_spi.h"

#define CMD_CHIP_ERASE          0xC7
#define CMD_ENABLE_WRITE        0x06
#define CMD_DISABLE_WRITE       0x04
#define CMD_POWER_DOWN          0xB9
#define CMD_READ                0x03
#define CMD_RELEASE_POWER_DOWN  0xAB
#define CMD_SECTOR_ERASE        0x20
#define CMD_STATUS              0x05
#define CMD_WRITE               0x02

void ice_sram_init(void) {
    ice_spi_init();

    // Not using the SPI peripheral to control CS because it only knows how to
    // toggle it every 4-16 bits while we need to keep the PSRAM selected for a
    // multi-byte read or write sequence.
    gpio_init(ICE_SRAM_CS_PIN);
    gpio_put(ICE_SRAM_CS_PIN, true);
    gpio_set_dir(ICE_SRAM_CS_PIN, GPIO_OUT);

    // The SRAM CS is active low
    gpio_set_outover(ICE_SRAM_CS_PIN, GPIO_OVERRIDE_INVERT);
}

uint8_t ice_sram_get_status(void) {
    const uint8_t command[] = { CMD_STATUS };
    uint8_t status;

    ice_spi_chip_select(ICE_SRAM_CS_PIN);
    ice_spi_write_blocking(command, sizeof(command));
    ice_spi_read_blocking(&status, sizeof(status));
    ice_spi_chip_deselect(ICE_SRAM_CS_PIN);
    return status;
}

void ice_sram_erase_chip(void) {
    const uint8_t command[] = { CMD_CHIP_ERASE };

    ice_spi_chip_select(ICE_SRAM_CS_PIN);
    ice_spi_write_blocking(command, sizeof(command));
    ice_spi_chip_deselect(ICE_SRAM_CS_PIN);
}

void ice_sram_erase_sector(uint32_t addr) {
    const uint8_t command[] = { CMD_SECTOR_ERASE, addr >> 16, addr >> 8, addr };

    assert(addr % ICE_SRAM_FLASH_PAGE_SIZE == 0);

    ice_spi_chip_select(ICE_SRAM_CS_PIN);
    ice_spi_write_blocking(command, sizeof(command));
    ice_spi_chip_deselect(ICE_SRAM_CS_PIN);
}

void ice_sram_power_off(void) {
    const uint8_t command[] = { CMD_RELEASE_POWER_DOWN };

    ice_spi_chip_select(ICE_SRAM_CS_PIN);
    ice_spi_write_blocking(command, sizeof(command));
    ice_spi_chip_deselect(ICE_SRAM_CS_PIN);

    sleep_us(5); // Takes around 3us of delay.
}

void ice_sram_power_on(void) {
    const uint8_t command[] = { CMD_POWER_DOWN };

    ice_spi_chip_select(ICE_SRAM_CS_PIN);
    ice_spi_write_blocking(command, sizeof(command));
    ice_spi_chip_deselect(ICE_SRAM_CS_PIN);
}

void ice_sram_enable_write(void) {
    const uint8_t command[] = { CMD_ENABLE_WRITE };

    ice_spi_chip_select(ICE_SRAM_CS_PIN);
    ice_spi_write_blocking(command, sizeof(command));
    ice_spi_chip_deselect(ICE_SRAM_CS_PIN);
}

void ice_sram_disable_write(void) {
    const uint8_t command[] = { CMD_DISABLE_WRITE };

    ice_spi_chip_select(ICE_SRAM_CS_PIN);
    ice_spi_write_blocking(command, sizeof(command));
    ice_spi_chip_deselect(ICE_SRAM_CS_PIN);
}

void ice_sram_write_async(uint32_t addr, const uint8_t *data, size_t data_size,
                          void (*callback)(volatile void *), void *context) {
    uint8_t command[] = { CMD_WRITE, addr >> 16, addr >> 8, addr };

    ice_spi_chip_select(ICE_SRAM_CS_PIN);
    ice_spi_write_blocking(command, sizeof(command));
    ice_spi_write_async(data, data_size, callback, context);
}

void ice_sram_write_blocking(uint32_t addr, const uint8_t *data, size_t data_size) {
    ice_sram_write_async(addr, data, data_size, NULL, NULL);
    ice_spi_wait_completion();
}

void ice_sram_read_async(uint32_t addr, uint8_t *data, size_t data_size,
                          void (*callback)(volatile void *), void *context) {
    uint8_t command[] = { CMD_READ, addr >> 16, addr >> 8, addr };

    ice_spi_chip_select(ICE_SRAM_CS_PIN);
    ice_spi_write_blocking(command, sizeof(command));
    ice_spi_write_async(data, data_size, callback, context);
}

void ice_sram_read_blocking(uint32_t addr, uint8_t *data, size_t data_size) {
    ice_sram_read_async(addr, data, data_size, NULL, NULL);
    ice_spi_wait_completion();
}
