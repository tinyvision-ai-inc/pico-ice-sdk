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
#include "pico/stdlib.h"

// pico-ice-sdk
#include "boards.h"
#include "ice_HAL.h"
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

static int ice_flash_wait(const ice_spibus spibus) {
    uint8_t cmds[] = { FLASH_CMD_STATUS, 0 };
    uint8_t buf[2];
    int ret;

    do {
        ice_hal_gpio_set_0(spibus.CS_flash);
        ret = ice_hal_spi_write(cmds, sizeof(cmds));
        ret |= ice_hal_spi_read(buf, sizeof(buf));
        ice_hal_gpio_set_1(spibus.CS_flash);
        if (ret < 0)
            return ret;
    } while (buf[1] & FLASH_STATUS_BUSY_MASK);
    return ret;
}

static int ice_flash_enable_write(const ice_spibus spibus) {
    uint8_t cmds[] = { FLASH_CMD_ENABLE_WRITE };
    int ret;

    ice_hal_gpio_set_0(spibus.CS_flash);
    ret = ice_hal_spi_write(cmds, sizeof cmds);
    ice_hal_gpio_set_1(spibus.CS_flash);

    return ret;
}

int ice_flash_erase_sector(const ice_spibus spibus, uint32_t addr) {
    uint8_t cmds[] = { FLASH_CMD_SECTOR_ERASE, addr >> 16, addr >> 8, addr };
    int ret;

    assert(addr % ICE_FLASH_SECTOR_SIZE == 0);

    ret = ice_flash_enable_write(spibus);
    if (ret < 0)
        return ret;

    ice_hal_gpio_set_0(spibus.CS_flash);
    ret = ice_hal_spi_write(cmds, sizeof cmds);
    ice_hal_gpio_set_1(spibus.CS_flash);
    if (ret < 0)
        return ret;

    ret = ice_flash_wait(spibus);
    return ret;
}

int ice_flash_program_page(const ice_spibus spibus, uint32_t addr, uint8_t const page[ICE_FLASH_PAGE_SIZE]) {
    uint8_t cmds[] = { FLASH_CMD_PROGRAM_PAGE, addr >> 16, addr >> 8, addr };
    int ret;

    assert(addr % ICE_FLASH_PAGE_SIZE == 0);

    ret = ice_flash_enable_write(spibus);
    if (ret < 0)
        return ret;

    ice_hal_gpio_set_0(spibus.CS_flash);
    ret = ice_hal_spi_write(cmds, sizeof cmds);
    ret |= ice_hal_spi_write(page, ICE_FLASH_PAGE_SIZE);
    ice_hal_gpio_set_1(spibus.CS_flash);
    if (ret < 0)
        return ret;

    ret = ice_flash_wait(spibus);
    return ret;
}

int ice_flash_read(const ice_spibus spibus, uint32_t addr, uint8_t *buf, size_t sz) {
    uint8_t cmds[] = { FLASH_CMD_READ, addr >> 16, addr >> 8, addr };
    int ret;

    ice_hal_gpio_set_0(spibus.CS_flash);
    ret = ice_hal_spi_write(cmds, sizeof cmds);
    if (ret < 0)
        return ret;
    ret = ice_hal_spi_read(buf, sz);
    ice_hal_gpio_set_1(spibus.CS_flash);

    return ret;
}

int ice_flash_erase_block(const ice_spibus spibus, uint32_t addr) {
    uint8_t cmds[] = { FLASH_CMD_BLOCK_ERASE, addr >> 16, addr >> 8, addr };
    int ret;

    assert(addr % ICE_FLASH_BLOCK_SIZE == 0);

    ret = ice_flash_enable_write(spibus);
    if (ret < 0)
        return ret;

    ice_hal_gpio_set_0(spibus.CS_flash);
    ret = ice_hal_spi_write(cmds, sizeof cmds);
    ice_hal_gpio_set_1(spibus.CS_flash);
    if (ret < 0)
        return ret;

    ret = ice_flash_wait(spibus);
    return ret;
}

int ice_flash_erase_chip(const ice_spibus spibus) {
    uint8_t cmds[] = { FLASH_CMD_CHIP_ERASE };
    int ret;

    ret = ice_flash_enable_write(spibus);
    if (ret < 0)
        return ret;

    ice_hal_gpio_set_0(spibus.CS_flash);
    ret = ice_hal_spi_write(cmds, sizeof cmds);
    ice_hal_gpio_set_1(spibus.CS_flash);
    if (ret < 0)
        return ret;

    ret = ice_flash_wait(spibus);
    return ret;
}

int ice_flash_wakeup(const ice_spibus spibus) {
    uint8_t cmds[] = { FLASH_CMD_RELEASE_POWERDOWN };
    int ret;

    ice_hal_gpio_set_0(spibus.CS_flash);
    ret = ice_hal_spi_write(cmds, sizeof cmds);
    ice_hal_gpio_set_1(spibus.CS_flash);
    if (ret < 0)
        return ret;

    ret = ice_flash_wait(spibus);
    return ret;
}

int ice_flash_sleep(const ice_spibus spibus) {
    uint8_t cmds[] = { FLASH_CMD_POWERDOWN };
    int ret;

    ice_hal_gpio_set_0(spibus.CS_flash);
    ret = ice_hal_spi_write(cmds, sizeof cmds);
    ice_hal_gpio_set_1(spibus.CS_flash);
    if (ret < 0)
        return ret;

    ret = ice_flash_wait(spibus);
    return ret;
}

int ice_flash_init(const ice_spibus spibus, int baudrate) {
    int ret;

    // Configure the SPI peripheral if not done already
    ret = ice_hal_spi_init(spibus.MOSI, spibus.MISO, spibus.SCK, baudrate);
    if (ret < 0)
        return ret;

    // Setup the CSN pin to GPIO mode for software control
    ice_hal_gpio_init(spibus.CS_flash);
    ice_hal_gpio_set_pu(spibus.CS_flash);

    // Flash might be asleep as a successful FPGA boot will put it to sleep as the last command!
    ret = ice_flash_wakeup(spibus);
    return ret;
}
