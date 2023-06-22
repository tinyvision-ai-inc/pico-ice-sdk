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

// TinyUSB
#include "tusb.h"
#include "tusb_config.h"

// pico-sdk
#include "pico/unique_id.h"

// Predefined macros to avoid repetitive
#define USB_VID             0x1209  // https://pid.codes/1209/
#define USB_PID             0xB1C0  // https://pid.codes/1209/B1C0/
#define USB_MANUFACTURER    "tinyVision.ai Inc."
#define USB_PRODUCT         "pico-ice"
#define USB_LANG_EN         (const char[]){ 0x09, 0x04 }
#define USB_VENDOR          "tinyVision.ai"
#define EPOUT               0x00
#define EPIN                0x80

#define CONFIG_TOTAL_LEN    (TUD_CONFIG_DESC_LEN \
    + CFG_TUD_CDC    * TUD_CDC_DESC_LEN \
    + CFG_TUD_MSC    * TUD_MSC_DESC_LEN \
    + CFG_TUD_HID    * TUD_HID_DESC_LEN \
    + CFG_TUD_MIDI   * TUD_MIDI_DESC_LEN \
    + CFG_TUD_VENDOR * TUD_VENDOR_DESC_LEN \
    + CFG_TUD_DFU    * TUD_DFU_DESC_LEN(CFG_TUD_DFU_ALT))

// Generated at random for the pico-ice as advised by https://github.com/microsoft/uf2/
#define ICE_UF2_FAMILY_ID 0x792e7263

// Simplify the declaration of string IDs
enum {
    STRID_LANGID,
    STRID_MANUFACTURER,
    STRID_PRODUCT,
    STRID_SERIAL_NUMBER,
    STRID_VENDOR,
    STRID_CDC = 10,
    STRID_MSC = 20,
    STRID_DFU = 30,
    STRID_NUM_TOTAL = 40
};

#ifdef __cplusplus
extern "C" {
#endif

extern char const *tud_string_desc[STRID_NUM_TOTAL];
extern char usb_serial_number[PICO_UNIQUE_BOARD_ID_SIZE_BYTES * 2 + 1];
extern uint8_t const tud_desc_configuration[CONFIG_TOTAL_LEN];
extern const tusb_desc_device_t tud_desc_device;
extern void (*tud_cdc_rx_cb_table[CFG_TUD_CDC])(uint8_t);

void ice_usb_init(void);
void ice_usb_sleep_ms(uint32_t ms);

#ifdef __cplusplus
}
#endif
