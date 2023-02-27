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

#include <assert.h>
#include "hardware/gpio.h"
#include "hardware/uart.h"
#include "hardware/watchdog.h"
#include "tusb.h"
#include "boards/pico_ice.h"
#include "ice_usb.h"
#include "ice_flash.h"
#include "ice_cram.h"
#include "ice_spi.h"
#include "ice_fpga.h"
#include "tinyuf2/uf2.h"
#include "tinyuf2/board_api.h"

char usb_serial_number[PICO_UNIQUE_BOARD_ID_SIZE_BYTES * 2 + 1];

#if ICE_USB_USE_DEFAULT_DESCRIPTOR

const tusb_desc_device_t tud_desc_device = {
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

static bool dfu_download_pending;

// Invoked when received GET DEVICE DESCRIPTOR
// Application return pointer to descriptor
uint8_t const *tud_descriptor_device_cb(void) {
    return (uint8_t const *)&tud_desc_device;
}

const uint8_t *tud_descriptor_configuration_cb(uint8_t index) {
    (void)index;
    return tud_desc_configuration;
}

// Invoked when received GET STRING DESCRIPTOR request
// Application return pointer to descriptor, whose contents must exist long enough for transfer to complete
uint16_t const *tud_descriptor_string_cb(uint8_t index, uint16_t langid) {
    static uint16_t utf16[32];
    uint8_t len;

    (void)langid;

    // Assign the SN using the unique flash id
    if (!usb_serial_number[0]) {
        pico_get_unique_board_id_string(usb_serial_number, sizeof(usb_serial_number));
    }

    if (index == STRID_LANGID) {
        memcpy(&utf16[1], tud_string_desc[STRID_LANGID], 2);
        len = 1;
    } else {
        const char *str;

        if (index >= sizeof(tud_string_desc) / sizeof(*tud_string_desc)) {
            return NULL;
        }

        str = tud_string_desc[index];

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

#endif // TUD_DESCRIPTOR

#if ICE_USB_USE_DEFAULT_CDC && CFG_TUD_CDC

void (*tud_cdc_rx_cb_table[CFG_TUD_CDC])(uint8_t);

#include "ice_led.h"

void tud_cdc_rx_cb(uint8_t cdc_num) {
    if (tud_cdc_rx_cb_table[cdc_num] != NULL) {
        // dispatch to the handler
        assert(cdc_num < sizeof tud_cdc_rx_cb_table / sizeof *tud_cdc_rx_cb_table);
        tud_cdc_rx_cb_table[cdc_num](cdc_num);
    } else {
        // discard the output
        tud_cdc_n_read_char(cdc_num);
    }
}

static void uart_to_cdc(uart_inst_t *uart, uint8_t cdc_num) {
    while (uart_is_readable(uart)) {
        tud_cdc_n_write_char(cdc_num, uart_getc(uart0));
        tud_cdc_n_write_flush(cdc_num);
    }
}

static void cdc_to_uart(uint8_t cdc_num, uart_inst_t *uart) {
    ice_led_red(true);
    while (tud_cdc_n_available(cdc_num)) {
        ice_led_green(true);
        uart_putc(uart, tud_cdc_n_read_char(cdc_num));
    }
}

void ice_usb_uart0_to_cdc0(void) {
    uart_to_cdc(uart0, 0);
}

void ice_usb_uart0_to_cdc1(void) {
    uart_to_cdc(uart0, 1);
}

void ice_usb_uart1_to_cdc0(void) {
    uart_to_cdc(uart1, 0);
}

void ice_usb_uart1_to_cdc1(void) {
    uart_to_cdc(uart1, 1);
}

void ice_usb_cdc_to_uart0(uint8_t cdc_num) {
    cdc_to_uart(cdc_num, uart0);
}

void ice_usb_cdc_to_uart1(uint8_t cdc_num) {
    cdc_to_uart(cdc_num, uart1);
}

#endif // ICE_USB_USE_DEFAULT_CDC

#if ICE_USB_USE_DEFAULT_DFU && CFG_TUD_DFU

// Invoked right before tud_dfu_download_cb() (state=DFU_DNBUSY) or tud_dfu_manifest_cb() (state=DFU_MANIFEST) Application return timeout in milliseconds (bwPollTimeout) for the next download/manifest operation.
// During this period, USB host won't try to communicate with us.
uint32_t tud_dfu_get_timeout_cb(uint8_t alt, uint8_t state) {
    return 0; // Request we are polled in 1ms
}

// Invoked when received DFU_DNLOAD (wLength>0) following by DFU_GETSTATUS (state=DFU_DNBUSY) requests
// This callback could be returned before flashing op is complete (async).
// Once finished flashing, application must call tud_dfu_finish_flashing()
void tud_dfu_download_cb(uint8_t alt, uint16_t block_num, const uint8_t *data, uint16_t length) {
    if (!dfu_download_pending) {
        dfu_download_pending = true;

        // make sure the RP2040 have full access to the bus
        ice_fpga_stop();
        ice_spi_init();

        if (alt == 0) {
            ice_cram_open();
        }
        if (alt == 1) {
            ice_flash_init();
        }
    }

    uint32_t dest_addr = block_num * CFG_TUD_DFU_XFER_BUFSIZE;

    for (uint32_t offset = 0; offset < length; offset += ICE_FLASH_PAGE_SIZE) {
        if (alt == 0) {
            ice_cram_write(data, length);
        }
        if (alt == 1) {
            if ((dest_addr + offset) % ICE_FLASH_SECTOR_SIZE == 0) {
                ice_flash_erase_sector(dest_addr + offset);
            }
            ice_flash_program_page(dest_addr + offset, data + offset);
        }
    }

    tud_dfu_finish_flashing(DFU_STATUS_OK);
}

// Invoked when download process is complete, received DFU_DNLOAD (wLength=0) following by DFU_GETSTATUS (state=Manifest) Application can do checksum, or actual flashing if buffered entire image previously.
// Once finished flashing, application must call tud_dfu_finish_flashing()
void tud_dfu_manifest_cb(uint8_t alt) {
    bool fpga_done;

    assert(dfu_download_pending);
    dfu_download_pending = false;
    if (alt == 0) {
        fpga_done = ice_cram_close();
    }
    if (alt == 1) {
        fpga_done = ice_fpga_start();
    }

    tud_dfu_finish_flashing(fpga_done ? DFU_STATUS_OK : DFU_STATUS_ERR_FIRMWARE);
}

// Called if -R option passed to dfu-util.
void tud_dfu_detach_cb(void) {
    watchdog_reboot(0, 0, 0);
}

#endif // ICE_USB_USE_DEFAULT_DFU
