/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2019 Ha Thach (tinyusb.org)
 * Copyright (c) 2022-2023 TinyVision.ai Inc.
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
 */

#include "pico/unique_id.h"
#include "tusb.h"
#include "ice_usb.h"

static const tusb_desc_device_t desc_device = {
    .bLength            = sizeof(tusb_desc_device_t),
    .bDescriptorType    = TUSB_DESC_DEVICE,
    .bcdUSB             = 0x0110,
    .bDeviceClass       = TUSB_CLASS_MISC,
    .bDeviceSubClass    = MISC_SUBCLASS_COMMON,
    .bDeviceProtocol    = MISC_PROTOCOL_IAD,
    .bMaxPacketSize0    = CFG_TUD_ENDPOINT0_SIZE,
    .idVendor           = USB_VID,
    .idProduct          = USB_PID,
    .bcdDevice          = 0x0100,
    .iManufacturer      = STRID_MANUFACTURER,
    .iProduct           = STRID_PRODUCT,
    .iSerialNumber      = STRID_SERIAL_NUMBER,
    .bNumConfigurations = 1
};

/*
 * Invoked when received GET DEVICE DESCRIPTOR
 * Application return pointer to descriptor
 */
uint8_t const *tud_descriptor_device_cb(void)
{
    return (uint8_t const *)&desc_device;
}

const uint8_t *tud_descriptor_configuration_cb(uint8_t index)
{
    (void)index;
    return tud_desc_configuration;
}

char usb_serial_number[PICO_UNIQUE_BOARD_ID_SIZE_BYTES * 2 + 1];

/*
 * Invoked when received GET STRING DESCRIPTOR request
 * Application return pointer to descriptor, whose contents must exist long enough for transfer to complete
 */
uint16_t const * tud_descriptor_string_cb(uint8_t index, uint16_t langid)
{
    static uint16_t utf16[32];
    uint8_t len;

    (void) langid;

    // Assign the SN using the unique flash id
    if (!usb_serial_number[0]) {
        pico_get_unique_board_id_string(usb_serial_number, sizeof(usb_serial_number));
    }

    if (index == 0) {
        memcpy(&utf16[1], string_desc_arr[0], 2);
        len = 1;
    } else {
        const char *str;

        if (index >= sizeof(string_desc_arr) / sizeof(*string_desc_arr)) {
            return NULL;
        }

        str = string_desc_arr[index];

        len = strlen(str);
        if (len > 31) {
            len = 31;
        }

        for (uint8_t i = 0; i < len; i++) {
            utf16[i + 1] = str[i];
        }
    }

    // first byte is length (including header), second byte is string type
    utf16[0] = (TUSB_DESC_STRING << 8) | (2 * len + 2);

    return utf16;
}
