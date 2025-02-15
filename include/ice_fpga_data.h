/*
 * MIT License
 *
 * Copyright (c) 2025 tinyVision.ai
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

#include "hardware/spi.h"

typedef struct {
	spi_inst_t	*peripheral;
	uint8_t		MISO;
	uint8_t		MOSI;
	uint8_t		SCK;
	uint8_t		CS_flash;
	uint8_t		CS_cram;
	uint8_t		CS_psram;
	uint8_t		CS_fpga;
} ice_spibus;

typedef struct {
	ice_spibus	bus;
	uint8_t		pin_cdone;
	uint8_t		pin_clock;
	uint8_t		pin_creset;
} ice_fpga;

extern const ice_fpga pico_fpga;
extern const ice_fpga pico2_fpga;
