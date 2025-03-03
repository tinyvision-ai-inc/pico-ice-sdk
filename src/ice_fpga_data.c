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

#include "ice_fpga_data.h"

const ice_spibus pico2_spibus = {
	.peripheral = spi0,
	.MISO = 4, //ICE_SI
	.MOSI = 7, //ICE_SO
	.SCK = 6, //ICE_SCK
	.CS_flash = 5, //ICE_SSN
	.CS_cram = 5,
	.CS_psram = -1, // No FPGA SRAM on pico2-ice
};

const ice_fpga pico2_fpga = {
	.bus = pico2_spibus,
	.pin_cdone = 40, //ICE_DONE_ADC0
	.pin_clock = 21, //ICE_CLK
	.pin_creset = 31, //ICE_RST
};

const ice_spibus pico_spibus = {
	.peripheral = spi1,
	.MISO = 8,
	.MOSI = 11,
	.SCK = 10,
	.CS_flash = 9,
	.CS_cram = 9,
	.CS_psram = 14,
};

const ice_fpga pico_fpga = {
	.bus = pico_spibus,
	.pin_cdone = 26,
	.pin_clock = 24,
	.pin_creset = 27,
};
