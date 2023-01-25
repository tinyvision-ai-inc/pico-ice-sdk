/* 
 * The MIT License (MIT)
 *
 * Copyright (c) 2021 Greg Steiert
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#ifndef _SCT_NEOPIXEL_H_
#define _SCT_NEOPIXEL_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

//--------------------------------------------------------------------+
// Neopixel Driver
//--------------------------------------------------------------------+
#define NEO_SCT           SCT0
#define NEO_MATCH_RISE    12
#define NEO_MATCH_PERIOD  13
#define NEO_MATCH_RESET   15
#define NEO_MATCH_0       0
#define NEO_MATCH_1       11
#define NEO_EVENT_RISE    12
// Use events 0-9 for channel specific events
#define NEO_EVENT_CH_0    0
#define NEO_EVENT_CH_1    1
#define NEO_EVENT_CH_2    2
#define NEO_EVENT_CH_3    3
#define NEO_EVENT_CH_4    4
#define NEO_EVENT_CH_5    5
#define NEO_EVENT_CH_6    6
#define NEO_EVENT_CH_7    7
#define NEO_EVENT_CH_8    8
#define NEO_EVENT_CH_9    9
#define NEO_EVENT_FALL_1  11
#define NEO_EVENT_NEXT    13
#define NEO_EVENT_LAST    14
#define NEO_EVENT_RESET   15
#define NEO_COUNT_RISE    1
#define NEO_COUNT_FALL0   31
#define NEO_COUNT_FALL1   61
#define NEO_COUNT_PERIOD  120
#define NEO_COUNT_RESET   8120
// State used for first bit
#define NEO_FIRST_BIT     23
#define NEO_SCT_OUTPUTS   10


void sctpix_init(uint32_t neoPixelType);
void sctpix_addCh(uint32_t ch, uint32_t *data, uint32_t size);
void sctpix_rmCh(uint32_t ch);
void sctpix_show(void);
bool sctpix_canShow(void);
void sctpix_setPixel(uint32_t ch, uint32_t pixel, uint32_t color);
void sctpix_updateType(uint32_t neoPixelType);


#ifdef __cplusplus
 }
#endif

#endif