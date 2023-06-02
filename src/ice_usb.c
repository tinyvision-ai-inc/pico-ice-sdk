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

// libc
#include <assert.h>

// pico-sdk
#include "hardware/gpio.h"
#include "hardware/uart.h"
#include "hardware/watchdog.h"
#include "pico/multicore.h"
#include "pico/stdlib.h"

// tinyusb
#include "tusb.h"

// pico-ice-sdk
#include "boards/pico_ice.h"
#include "ice_usb.h"
#include "ice_flash.h"
#include "ice_cram.h"
#include "ice_spi.h"
#include "ice_fpga.h"

// microsoft uf2
#include "uf2.h"

// tinyuf2
#include "board_api.h"

#define WATCHDOG_DELAY 3000

#define CONCAT(a,b,c,d)     a ## b ## c ## d
#define CONCAT2(a,b)        CONCAT(a,b,,)
#define ICE_USB_UART        CONCAT2(uart, ICE_USB_UART_NUM)

// Provide a default config where some fields come be customized in <tusb_config.h>
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

// Also used in usb_descriptors.c.
char usb_serial_number[PICO_UNIQUE_BOARD_ID_SIZE_BYTES * 2 + 1];

// Sleeping without calling tud_task() hangs the USB stack in the meantime.
void ice_usb_sleep_ms(uint32_t ms) {
    while (ms-- > 0) {
        tud_task();
        sleep_ms(1);
    }
}

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
    if (usb_serial_number[0] == '\0') {
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


#if ICE_USB_USE_DEFAULT_CDC

#ifdef ICE_USB_UART_CDC

static void ice_usb_cdc_to_uart(uint8_t byte) {
    if (uart_is_writable(ICE_USB_UART)) {
        uart_putc(ICE_USB_UART, byte);
    }
}

static void ice_usb_uart_to_cdc(void) {
    while (uart_is_readable(ICE_USB_UART)) {
        uint8_t byte = uart_getc(ICE_USB_UART);
        tud_cdc_n_write_char(ICE_USB_UART_CDC, byte);
        tud_cdc_n_write_flush(ICE_USB_UART_CDC);
    }
}

#endif

#ifdef ICE_USB_FPGA_CDC

void ice_wishbone_serial_tx_cb(uint8_t byte) {
    tud_cdc_n_write_char(ICE_USB_FPGA_CDC, byte);
    tud_cdc_n_write_flush(ICE_USB_FPGA_CDC);
}

void ice_wishbone_serial_read_cb(uint32_t addr, uint8_t *buf, size_t size) {
    ice_fpga_read(addr, buf, size);
}

void ice_wishbone_serial_write_cb(uint32_t addr, uint8_t *buf, size_t size) {
    ice_fpga_write(addr, buf, size);
}

// Parse input data from a serial link (such as CDC uart) and control
// an SPI peripheral to query the FPGA registers and send an answer back.
void ice_usb_cdc_to_fpga(uint8_t byte) {
    ice_wishbone_serial(byte);
}

#endif

void (*ice_usb_cdc_table[CFG_TUD_CDC])(uint8_t) = {
#ifdef ICE_USB_UART_CDC
    [ICE_USB_UART_CDC] = &ice_usb_cdc_to_uart,
#endif
#ifdef ICE_USB_FPGA_CDC
    [ICE_USB_FPGA_CDC] = &ice_usb_cdc_to_fpga,
#endif
};

void tud_cdc_rx_cb(uint8_t cdc_num) {
    // existing callback for that CDC number, send it all available data
    assert(cdc_num < sizeof(ice_usb_cdc_table) / sizeof(*ice_usb_cdc_table));

    while (tud_cdc_n_available(cdc_num)) {
        uint8_t byte = tud_cdc_n_read_char(cdc_num);
        if (ice_usb_cdc_table[cdc_num] != NULL) {
            ice_usb_cdc_table[cdc_num](byte);
        }
    }
}

#endif // ICE_USB_USE_DEFAULT_CDC


#if ICE_USB_USE_DEFAULT_DFU

// Invoked right before tud_dfu_download_cb() (state=DFU_DNBUSY) or tud_dfu_manifest_cb() (state=DFU_MANIFEST)
// Application return timeout in milliseconds (bwPollTimeout) for the next download/manifest operation.
// During this period, USB host won't try to communicate with us.
uint32_t tud_dfu_get_timeout_cb(uint8_t alt, uint8_t state) {
    return 0; // Request we are polled in 1ms
}

// Invoked when received DFU_DNLOAD (wLength>0) following by DFU_GETSTATUS (state=DFU_DNBUSY) requests
// This callback could be returned before flashing op is complete (async).
// Once finished flashing, application must call tud_dfu_finish_flashing()
void tud_dfu_download_cb(uint8_t alt, uint16_t block_num, const uint8_t *data, uint16_t length) {
    static bool started = false;
    if (!started) {
        // When this returns, we have reserved use of the serial memory SPI bus.
        // TODO: uncomment when ice_smem.c is working again.
        //ice_smem_await_async_completion();

        // Disable all interrupts except USB.
        irq_set_mask_enabled(~(1 << USBCTRL_IRQ), false);

        // Soft reset core 1.
        // TODO: if we get unlucky, core 1 might reset while holding a TinyUSB lock, in which case DFU download might hang.
        multicore_reset_core1();

        // Ensure eventual reboot in case user doesn't pass -R to dfu-util
        watchdog_enable(WATCHDOG_DELAY, true /* pause_on_debug */);

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

    watchdog_update();

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

    // Never return to the main loop.
    if (!started) {
        started = true;
        for (;;) {
            tud_task();
        }
    }
}

// Invoked when download process is complete, received DFU_DNLOAD (wLength=0) following by DFU_GETSTATUS (state=Manifest) Application can do checksum, or actual flashing if buffered entire image previously.
// Once finished flashing, application must call tud_dfu_finish_flashing()
void tud_dfu_manifest_cb(uint8_t alt) {
    bool fpga_done;

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


// Init everything as declared in <tusb_config.h>
void ice_usb_init(void) {
    tusb_init();

#ifdef ICE_USB_UART_NUM
    irq_set_exclusive_handler(UART0_IRQ + ICE_USB_UART_NUM, ice_usb_uart_to_cdc);
    irq_set_enabled(UART0_IRQ + ICE_USB_UART_NUM, true);
    uart_set_irq_enables(ICE_USB_UART, true, false);
#endif

#ifdef ICE_USB_USE_TINYUF2_MSC
    board_init();
    uf2_init();
#endif
}
