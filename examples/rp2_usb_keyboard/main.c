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

#include "pico/stdlib.h"
#include "ice_led.h"
#include "tusb.h"

#define MAX_REPORT  4

static struct {
    uint8_t report_count;
    tuh_hid_report_info_t report_info[MAX_REPORT];
} g_hid_info[CFG_TUH_HID];

// Invoked when device with hid interface is mounted
void tuh_hid_mount_cb(uint8_t dev_addr, uint8_t instance, const uint8_t *desc_report, uint16_t desc_len) {
    // Interface protocol (hid_interface_protocol_enum_t)
    uint8_t itf_protocol = tuh_hid_interface_protocol(dev_addr, instance);

    // By default host stack will use activate boot protocol on supported interface.
    // Therefore for this simple example, we only need to parse generic report descriptor (with built-in parser)
    if (itf_protocol == HID_ITF_PROTOCOL_NONE) {
        g_hid_info[instance].report_count = tuh_hid_parse_report_descriptor(g_hid_info[instance].report_info, MAX_REPORT, desc_report, desc_len);
    }

    // request to receive report
    // tuh_hid_report_received_cb() will be invoked when report is available
    tuh_hid_receive_report(dev_addr, instance);
}

// Invoked when device with hid interface is un-mounted
void tuh_hid_umount_cb(uint8_t dev_addr, uint8_t instance) {
}

// Invoked when report is available.
void tuh_hid_report_received_cb(uint8_t dev_addr, uint8_t instance, const uint8_t *report, uint16_t len) {
    uint8_t itf_protocol = tuh_hid_interface_protocol(dev_addr, instance);

    if (itf_protocol == HID_ITF_PROTOCOL_KEYBOARD) {
        const hid_keyboard_report_t *kbd_report = (const hid_keyboard_report_t *) report;

        for (int i = 0; i < count_of(kbd_report->keycode); ++i) {
            int key_code = kbd_report->keycode[i];
            if (key_code == 0) continue;

            // Output 8-bit key code as short blink for 0 bit, long blink for 1 bit.
            for (int i = 0; i < 8; ++i) {
                ice_led_red(false);
                sleep_ms(key_code & 1 ? 25 : 50);
                ice_led_red(true);
                sleep_ms(50);

                key_code >>= 1;
            }
        }
    }

    tuh_hid_receive_report(dev_addr, instance);
}

int main(void) {
    tusb_init();
    ice_led_init();

    while (1) {
        tuh_task();
    }

    return 0;
}
