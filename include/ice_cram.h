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
 * @defgroup ice_cram
 * @brief FPGA CRAM access
 * @{
 */

#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include "ice_fpga_data.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Reset the iCE40 and set it to CRAM configuration mode and prepare the
 *  incoming SPI transfer.
 */
bool ice_cram_open(const ice_fpga fpga);

/**
 * @brief Send the bitstream to the iCE40 CRAM, which configures the FPGA
 *  circuitry.
 *
 * @param buf pointer to bitstream data to flush to the iCE40
 * @param len size of that buffer
 */
void ice_cram_write(const uint8_t *buf, size_t len);

/**
 * @brief Terminate the SPI transaction and prepare the FPGA to start,
 *  waiting until it finishes booting.
 * 
 * @return true if the FPGA configuration succeeded or `false` if it timed out.
 */
bool ice_cram_close(void);

#ifdef __cplusplus
}
#endif

/** @} */
