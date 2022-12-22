#include "ice_fpga.h"
#include "pico/stdlib.h"
#include "tusb.h"

#define MAX_REPORT  4

static struct {
    uint8_t report_count;
    tuh_hid_report_info_t report_info[MAX_REPORT];
} g_hid_info[CFG_TUH_HID];

// Invoked when device with hid interface is mounted
void tuh_hid_mount_cb(uint8_t dev_addr, uint8_t instance, uint8_t const* desc_report, uint16_t desc_len) {
    // Interface protocol (hid_interface_protocol_enum_t)
    uint8_t const itf_protocol = tuh_hid_interface_protocol(dev_addr, instance);

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
void tuh_hid_report_received_cb(uint8_t dev_addr, uint8_t instance, uint8_t const* report, uint16_t len) {
    uint8_t const itf_protocol = tuh_hid_interface_protocol(dev_addr, instance);

    if (itf_protocol == HID_ITF_PROTOCOL_KEYBOARD) {
        const hid_keyboard_report_t* kbd_report = (const hid_keyboard_report_t*) report;

        for (int i = 0; i < count_of(kbd_report->keycode); ++i) {
            int key_code = kbd_report->keycode[i];
            if (key_code == 0) continue;

            // Output 8-bit key code as short blink for 0 bit, long blink for 1 bit.
            for (int i = 0; i < 8; ++i) {
                gpio_put(ICE_LED_RED_PIN, false);
                sleep_ms(key_code & 1 ? 25 : 50);
                gpio_put(ICE_LED_RED_PIN, true);
                sleep_ms(50);

                key_code >>= 1;
            }
        }
    }

    tuh_hid_receive_report(dev_addr, instance);
}

int main(void) {
    // Initialize as a USB host.
    tusb_init();

    // Don't call ice_sdk_init because that would initialize as a USB device.
    // Instead, initialize individual SDK modules.
    ice_fpga_init();

    gpio_init(ICE_LED_RED_PIN);
    gpio_put(ICE_LED_RED_PIN, true); // active-low
    gpio_set_dir(ICE_LED_RED_PIN, GPIO_OUT);

    for (;;) {
        // Periodically call this to invoke pending TinyUSB callbacks.
        tuh_task();
    }

    return 0;
}
