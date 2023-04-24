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

#pragma once

#include <stdint.h>
#include <stddef.h>
#include "boards/pico_ice.h"

// This module is not thread safe.

#define ICE_SRAM_STATUS_BUSY_MASK  0x01
#define ICE_SRAM_FLASH_PAGE_SIZE   0x100

#ifdef __cplusplus
extern "C" {
#endif

void ice_sram_init(void);
uint8_t ice_sram_get_status(void);
void ice_sram_power_on(void);
void ice_sram_power_off(void);
void ice_sram_erase_chip(void);
void ice_sram_erase_sector(uint32_t addr);
void ice_sram_enable_write(void);
void ice_sram_disnable_write(void);
void ice_sram_read_async(uint32_t addr, uint8_t *data, size_t data_size, void (*callback)(volatile void *), void *context);
void ice_sram_read_blocking(uint32_t addr, uint8_t *data, size_t data_size);
void ice_sram_write_async(uint32_t addr, const uint8_t *data, size_t data_size, void (*callback)(volatile void *), void *context);
void ice_sram_write_blocking(uint32_t addr, const uint8_t *data, size_t data_size);

#ifdef __cplusplus
}
#endif
