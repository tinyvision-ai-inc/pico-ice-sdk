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
#include <stdio.h>

// pico-sdk
#include "hardware/structs/spi.h"
#include "pico/stdlib.h"

// pico-ice-sdk
#include "boards.h"
#include "ice_spi.h"
#include "ice_flash.h"
#include "ice_led.h"

#define FLASH_CMD_PROGRAM_PAGE       0x02
#define FLASH_CMD_READ               0x03
#define FLASH_CMD_ENABLE_WRITE       0x06
#define FLASH_CMD_STATUS             0x05
#define FLASH_CMD_SECTOR_ERASE       0x20
#define FLASH_CMD_BLOCK_ERASE        0xD8
#define FLASH_CMD_CHIP_ERASE         0xC7
#define FLASH_CMD_RELEASE_POWERDOWN  0xAB
#define FLASH_CMD_POWERDOWN          0xB9

#define FLASH_STATUS_BUSY_MASK       0x01

static void ice_flash_wait(const ice_spibus spibus) {
    uint8_t cmds[] = { FLASH_CMD_STATUS, 0 };
    uint8_t buf[2];

    do {
        ice_spi_chip_select(spibus.CS_flash);
        ice_spi_write_blocking(cmds, sizeof(cmds));
        ice_spi_read_blocking(buf, sizeof(buf));
        ice_spi_chip_deselect(spibus.CS_flash);
    } while (buf[1] & FLASH_STATUS_BUSY_MASK);
}

static void ice_flash_enable_write(const ice_spibus spibus) {
    uint8_t cmds[] = { FLASH_CMD_ENABLE_WRITE };

    ice_spi_chip_select(spibus.CS_flash);
    ice_spi_write_blocking(cmds, sizeof cmds);
    ice_spi_chip_deselect(spibus.CS_flash);
}

void ice_flash_erase_sector(const ice_spibus spibus, uint32_t addr) {
    uint8_t cmds[] = { FLASH_CMD_SECTOR_ERASE, addr >> 16, addr >> 8, addr };

    assert(addr % ICE_FLASH_SECTOR_SIZE == 0);

    ice_flash_enable_write(spibus);

    ice_spi_chip_select(spibus.CS_flash);
    ice_spi_write_blocking(cmds, sizeof cmds);
    ice_spi_chip_deselect(spibus.CS_flash);

    ice_flash_wait(spibus);
}

void ice_flash_program_page(const ice_spibus spibus, uint32_t addr, uint8_t const page[ICE_FLASH_PAGE_SIZE]) {
    uint8_t cmds[] = { FLASH_CMD_PROGRAM_PAGE, addr >> 16, addr >> 8, addr };

    assert(addr % ICE_FLASH_PAGE_SIZE == 0);

    ice_flash_enable_write(spibus);

    ice_spi_chip_select(spibus.CS_flash);
    ice_spi_write_blocking(cmds, sizeof cmds);
    ice_spi_write_blocking(page, ICE_FLASH_PAGE_SIZE);
    ice_spi_chip_deselect(spibus.CS_flash);

    ice_flash_wait(spibus);
}

void ice_flash_read(const ice_spibus spibus, uint32_t addr, uint8_t *buf, size_t sz) {
    uint8_t cmds[] = { FLASH_CMD_READ, addr >> 16, addr >> 8, addr };

    ice_spi_chip_select(spibus.CS_flash);
    ice_spi_write_blocking(cmds, sizeof cmds);
    ice_spi_read_blocking(buf, sz);
    ice_spi_chip_deselect(spibus.CS_flash);
}

void ice_flash_erase_block(const ice_spibus spibus, uint32_t addr) {
    uint8_t cmds[] = { FLASH_CMD_BLOCK_ERASE, addr >> 16, addr >> 8, addr };

    assert(addr % ICE_FLASH_BLOCK_SIZE == 0);

    ice_flash_enable_write(spibus);

    ice_spi_chip_select(spibus.CS_flash);
    ice_spi_write_blocking(cmds, sizeof cmds);
    ice_spi_chip_deselect(spibus.CS_flash);

    ice_flash_wait(spibus);
}

void ice_flash_erase_chip(const ice_spibus spibus) {
    uint8_t cmds[] = { FLASH_CMD_CHIP_ERASE };

    ice_flash_enable_write(spibus);

    ice_spi_chip_select(spibus.CS_flash);
    ice_spi_write_blocking(cmds, sizeof cmds);
    ice_spi_chip_deselect(spibus.CS_flash);

    ice_flash_wait(spibus);
}

void ice_flash_wakeup(const ice_spibus spibus) {
    uint8_t cmds[] = { FLASH_CMD_RELEASE_POWERDOWN };

    ice_spi_chip_select(spibus.CS_flash);
    ice_spi_write_blocking(cmds, sizeof cmds);
    ice_spi_chip_deselect(spibus.CS_flash);

    ice_flash_wait(spibus);
}

void ice_flash_sleep(const ice_spibus spibus) {
    uint8_t cmds[] = { FLASH_CMD_POWERDOWN };

    ice_spi_chip_select(spibus.CS_flash);
    ice_spi_write_blocking(cmds, sizeof cmds);
    ice_spi_chip_deselect(spibus.CS_flash);

    ice_flash_wait(spibus);
}

void ice_flash_init(const ice_spibus spibus) {
    // Configure the SPI peripheral if not done already
    ice_spi_init(spibus);

    // Setup the CSN pin to GPIO mode for software control
    ice_spi_init_cs_pin(spibus.CS_flash, false);

    // Flash might be asleep as a successful FPGA boot will put it to sleep as the last command!
    ice_flash_wakeup(spibus);
}
