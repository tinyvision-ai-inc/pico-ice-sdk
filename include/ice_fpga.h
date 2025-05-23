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
 * @defgroup ice_fpga
 * @brief FPGA I/O and control
 * @{
 *
 * Depending on the RTL loaded onto the FPGA, it can use its internal RC
 * oscillator or a more accurate clock signal provided by the RP2040. This
 * library allows to configure this signal, control the FPGA startup, and
 * communicate over SPI to the same pins used for SRAM or FLASH access.
 * An LED pin is used for communicating with the FPGA.
 */

#pragma once
#include <stdint.h>
#include <stdbool.h>

#include "ice_fpga_data.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Let the FPGA start and export a clock for it over `ICE_FPGA_CLOCK_PIN`.
 * @param freq_mhz Exported clock frequency in MHz. Valid values: 48MHz, 24MHz,
 *  16MHz 12MHz, 8MHz, 6MHz, 4MHz, 3MHz, 2MHz, 1MHz.
 *
 * The RP2040 exports its own crystal-based clock to the iCE40, through the
 * dedicated [`CLOCK GPOUT0`](https://datasheets.raspberrypi.com/rp2040/rp2040-datasheet.pdf)
 * feature.
 * @return 0 on success, negative on fail
 */
int ice_fpga_init(const ice_fpga fpga, uint8_t freq_mhz);

/**
 * @brief Release the stop mode if it was present, and wait that the FPGA
 *  confirms its startup with ICE_FPGA_CDONE_PIN.
 * @return 0 on success, negative on fail
 */
int ice_fpga_start(const ice_fpga fpga);

/**
 * @brief Set the ICE_FPGA_CRESET_B_PIN to LOW which keeps the FPGA in reset
 *  mode.
 * @return 0 on success, negative on fail
 */
int ice_fpga_stop(const ice_fpga fpga);

/**
 * @brief Set the ICE_FPGA_CRESET_B_PIN to LOW which keeps the FPGA in reset
 *  mode.
 * @return 0 on success, negative on fail
 */
int ice_fpga_stop(const ice_fpga fpga);

/**
 * @brief deinit and free FPGA and associated resources
 * @return 0 on success, negative on fail
 */
int ice_fpga_deinit(const ice_fpga fpga);

#ifdef __cplusplus
}
#endif

/** @} */
