/* 
 * The MIT License (MIT)
 *
 * Copyright (c) 2019 Ha Thach (tinyusb.org)
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

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "board_api.h"
#include "uf2.h"
#include "tusb.h"

//--------------------------------------------------------------------+
// MACRO CONSTANT TYPEDEF PROTYPES
//--------------------------------------------------------------------+
//#define USE_DFU_BUTTON    1

// timeout for double tap detection
#define DBL_TAP_DELAY             500

#ifndef DBL_TAP_REG
// defined by linker script
extern uint32_t _board_dfu_dbl_tap[];
#define DBL_TAP_REG   _board_dfu_dbl_tap[0]
#endif

uint8_t const RGB_USB_UNMOUNTED[] = { 0xff, 0x00, 0x00 }; // Red
uint8_t const RGB_USB_MOUNTED[]   = { 0x00, 0xff, 0x00 }; // Green
uint8_t const RGB_WRITING[]       = { 0xcc, 0x66, 0x00 };
uint8_t const RGB_DOUBLE_TAP[]    = { 0x80, 0x00, 0xff }; // Purple
uint8_t const RGB_UNKNOWN[]       = { 0x00, 0x00, 0x88 }; // for debug
uint8_t const RGB_OFF[]           = { 0x00, 0x00, 0x00 };

static volatile uint32_t _timer_count = 0;

//--------------------------------------------------------------------+
// Device callbacks
//--------------------------------------------------------------------+

// Invoked when device is plugged and configured
void tud_mount_cb(void)
{
  indicator_set(STATE_USB_PLUGGED);
}

// Invoked when device is unplugged
void tud_umount_cb(void)
{
  indicator_set(STATE_USB_UNPLUGGED);
}

//--------------------------------------------------------------------+
// Indicator
//--------------------------------------------------------------------+

static uint32_t _indicator_state = STATE_BOOTLOADER_STARTED;
static uint8_t _indicator_rgb[3];

void indicator_set(uint32_t state)
{
  _indicator_state = state;
  switch(state)
  {
    case STATE_USB_UNPLUGGED:
      board_timer_start(1);
      memcpy(_indicator_rgb, RGB_USB_UNMOUNTED, 3);
      board_rgb_write(_indicator_rgb);
    break;

    case STATE_USB_PLUGGED:
      board_timer_start(5);
      memcpy(_indicator_rgb, RGB_USB_MOUNTED, 3);
      board_rgb_write(_indicator_rgb);
    break;

    case STATE_WRITING_STARTED:
      board_timer_start(25);
      memcpy(_indicator_rgb, RGB_WRITING, 3);
    break;

    case STATE_WRITING_FINISHED:
      board_timer_stop();
      board_rgb_write(RGB_WRITING);
    break;

    default: break; // nothing to do
  }
}

void board_timer_handler(void)
{
  _timer_count++;

  switch (_indicator_state)
  {
    case STATE_USB_UNPLUGGED:
    case STATE_USB_PLUGGED:
    {
      // Fading with LED TODO option to skip for unsupported MCUs
      uint8_t duty = _timer_count & 0xff;
      if ( _timer_count & 0x100 ) duty = 255 - duty;
      board_led_write(duty);

      // Skip RGB fading since it is too similar to CircuitPython
      // uint8_t rgb[3];
      // rgb_brightness(rgb, _indicator_rgb, duty);
      // board_rgb_write(rgb);
    }
    break;

    case STATE_WRITING_STARTED:
    {
      // Fast toggle with both LED and RGB
      bool is_on = _timer_count & 0x01;

      // fast blink LED if available
      board_led_write(is_on ? 0xff : 0x000);

      // blink RGB if available
      board_rgb_write(is_on ? _indicator_rgb : RGB_OFF);
    }
    break;

    default: break; // nothing to do
  }
}
