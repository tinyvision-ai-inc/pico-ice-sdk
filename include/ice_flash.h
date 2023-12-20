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

/**
 * @defgroup ice_flash
 * @brief Flash chip I/O
 * @{
 *
 * All these functions act on the on-board flash chip.
 * For a generic flash memory I/O, you can see the low-level [`ice_smem.h`](ice_smem.html)
 */

#pragma once
#include <stdint.h>
#include <stddef.h>

/**
 * @brief The size of the flash
 */
#define ICE_FLASH_PAGE_SIZE         256
#define ICE_FLASH_SECTOR_SIZE       4096
#define ICE_FLASH_BLOCK_SIZE        65536

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initialise the SPI1 peripheral, dedicated to flashing the FPGA.
 */
void ice_flash_init(void);

/**
 * @brief Communicate to the chip over SPI and read multiple bytes at chosen
 *  address onto onto a buffer.
 * @param addr The address at which the data is read.
 * @param data The buffer onto which the data read is stored.
 * @param data_size The size of the buffer in bytes.
 */
void ice_flash_read(uint32_t addr, uint8_t *buf, size_t sz);

/**
 * @brief Erase a sector of the flash chip at the given address.
 * @param addr The beginning of the sector.
 */
void ice_flash_erase_sector(uint32_t addr);

/**
 * @brief Program a page of the flash chip at the given address.
 * @param addr The address at which the data is written.
 * @param data The buffer holding the data to be sent to the flash chip, of
 *  size @ref ICE_FLASH_PAGE_SIZE.
 */
void ice_flash_program_page(uint32_t addr, uint8_t const page[ICE_FLASH_PAGE_SIZE]);

/**
 * @brief Send a command to erase a whole block.
 * @param addr The address at which the data is written.
 */
void ice_flash_erase_block(uint32_t addr);

/**
 * @brief Send a command to erase the whole chip.
 */
void ice_flash_erase_chip(void);

/**
 * @brief Send a command to wakeup the chip.
 */
void ice_flash_wakeup(void);

/**
 * @brief Send a command to put the chip to sleep.
 */
void ice_flash_sleep(void);

#ifdef __cplusplus
}
#endif

/** @} */
