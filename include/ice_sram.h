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
 * @defgroup ice_sram
 * @brief SRAM chip I/O
 * @{
 *
 * The SRAM chip is
 * [APS6404L-3SQN](https://www.apmemory.com/wp-content/uploads/APM_PSRAM_E3_QSPI_APS6404L-3SQN-v2.6-KGD_PKG.pdf).
 */

#pragma once
#include <stdint.h>
#include <stddef.h>
#include "boards.h"

#include "ice_fpga_data.h"

// This module is not thread safe.

#define ICE_SRAM_STATUS_BUSY_MASK  0x01

// Long transfers to/from the SRAM should be avoided as CS should not be
// asserted for more than 8us.  Holding CS for too long can result in data loss.
#define ICE_SRAM_TRANSFER_SIZE     32

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Send an initialization command to the SRAM chip.
 */
void ice_sram_init(const ice_spibus spibus);

/**
 * @brief Send a reset command to the SRAM chipo.
 */
void ice_sram_reset(const ice_spibus spibus);

/**
 * @brief Obtain the chip ID from the SRAM chip.
 * @param id Buffer to which the ID is written.
 *
 * The format is:
 * 
 * - 8 bits - Manufacturer ID (MF ID) - 0x0D for AP Memory
 * - 8 bits - Known Good Die (KGD) - 0b01010101 if pass, 0b01011101 if fail
 * - 3 bits - Density EID - A code for memory size
 * - 45 bits - EID - the rest of the chip identifier
 */
void ice_sram_get_id(const ice_spibus spibus, uint8_t id[8]);

/**
 * @brief Calling this function when any SPI transfer is in progress on this bus waits for it then starts.
 * @param addr Address to which write the data.
 * @param data Buffer with the data to send.
 * @param data_size Size of this buffer in bytes.
 * @param callback Function called once the transfer is complete.
 * @param context Argument passed to that function.
 *
 * Calling this function when a transfer is in progress waits then starts.
 */
void ice_sram_write_async(const ice_spibus spibus, uint32_t addr, const uint8_t *data, size_t data_size, void (*callback)(volatile void *), void *context);

/**
 * @brief Write a buffer to the flash chip and wait until completion.
 * @param addr Address to which write the data.
 * @param data Buffer with the data to send.
 * @param data_size Size of this buffer in bytes.
 */
void ice_sram_write_blocking(const ice_spibus spibus, uint32_t addr, const uint8_t *data, size_t data_size);

/**
 * @brief Read a buffer from the flash chip in the background, with a callback
 *  called once done.
 * @param addr Address from which read the data.
 * @param data Buffer to which save the data read.
 * @param data_size Size of this buffer in bytes.
 * @param callback Function called once the transfer is complete.
 * @param context Argument passed to that function.
 *
 * Calling this function when any SPI transfer is in progress on this bus waits
 * for it then starts.
 */
void ice_sram_read_async(const ice_spibus spibus, uint32_t addr, uint8_t *data, size_t data_size, void (*callback)(volatile void *), void *context);

/**
 * @brief Read a buffer from the flash chip and wait until completion.
 * @param addr Address from which read the data.
 * @param data Buffer to which save the data read.
 * @param data_size Size of this buffer in bytes.
 */
void ice_sram_read_blocking(const ice_spibus spibus, uint32_t addr, uint8_t *data, size_t data_size);

#ifdef __cplusplus
}
#endif

/** @} */
