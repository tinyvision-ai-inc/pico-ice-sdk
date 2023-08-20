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
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

void ice_spi_init(void);
void ice_spi_init_cs_pin(uint8_t cs_pin, bool active_high);
void ice_spi_chip_select(uint8_t cs_pin);
void ice_spi_chip_deselect(uint8_t csn_pin);
void ice_spi_write_async(const uint8_t *data, size_t data_size, void (*callback)(volatile void *), void *context);
void ice_spi_write_blocking(const uint8_t *data, size_t data_size);
void ice_spi_read_async(uint8_t *data, size_t data_size, void (*callback)(volatile void *), void *context);
void ice_spi_read_blocking(uint8_t *data, size_t data_size);
bool ice_spi_is_async_complete(void);
void ice_spi_wait_completion(void);

#ifdef __cplusplus
}
#endif
