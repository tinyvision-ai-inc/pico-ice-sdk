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
#ifndef BOARDS_H_
#define BOARDS_H_

#ifdef PICO2_ICE
#include "boards/pico2_ice.h"
#elif defined(PICO_ICE)
#include "boards/pico_ice.h"
#else
#error "pico-ice board model not found, check the value of PICO_BOARD"
#endif

#define ICE_FLASH_BAUDRATE 10000000

// Allow compilation of TinyUF2 without changing any source file.
// For board detection
#define TINYVISION_AI_INC_PICO_ICE
#define UF2_VERSION         "0"
#define UF2_INDEX_URL       "https://pico-ice.tinyvision.ai/"
#define UF2_VOLUME_LABEL    PICO_ICE_BOARD_NAME
#define UF2_PRODUCT_NAME    PICO_ICE_BOARD_NAME
#define UF2_BOARD_ID        PICO_ICE_BOARD_NAME
#define BOARD_UF2_FAMILY_ID ICE_UF2_FAMILY_ID

#endif
