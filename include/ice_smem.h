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

#define ICE_SMEM_STATUS_BUSY_MASK  0x01
#define ICE_SMEM_FLASH_PAGE_SIZE   0x100

#ifdef __cplusplus
extern "C" {
#endif

void ice_smem_init(uint baudrate, int irq);
void ice_smem_deinit(void);
bool ice_smem_is_async_complete(void);
void ice_smem_await_async_completion(void);
uint8_t ice_smem_get_status(uint cs_pin);
void ice_smem_erase_chip(uint cs_pin);
void ice_smem_erase_sector(uint cs_pin, uint32_t dest_addr);
void ice_smem_enable_write(uint cs_pin);
void ice_smem_disnable_write(uint cs_pin);
void ice_smem_write(uint cs_pin, uint32_t dest_addr, const void *src, uint32_t size);
void ice_smem_read(uint cs_pin, void *dest, uint32_t src_addr, uint32_t size);
void ice_smem_power_on(uint cs_pin);
void ice_smem_power_off(uint cs_pin);
void ice_smem_write_async(uint cs_pin, uint32_t dest_addr, const void *src, uint32_t size, void (*callback)(void *), void *context);
void ice_smem_read_async(uint cs_pin, void *dest, uint32_t src_addr, uint32_t size, void (*callback)(void *), void *context);
void ice_smem_output_command(uint cs_pin, const uint8_t *command, uint32_t command_size, const void *data, uint32_t data_size);
void ice_smem_output_command_async(uint cs_pin, const uint8_t *command, uint32_t command_size, const void *data, uint32_t data_size, void (*callback)(void *), void *context);
void ice_smem_input_command(uint cs_pin, const uint8_t *command, uint32_t command_size, void *data, uint32_t data_size);
void ice_smem_input_command_async(uint cs_pin, const uint8_t *command, uint32_t command_size, void *data, uint32_t data_size, void (*callback)(void *), void *context);

#ifdef __cplusplus
}
#endif
