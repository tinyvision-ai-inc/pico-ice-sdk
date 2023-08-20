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

#ifdef ICE_USB_UART_CDC
#error ICE_USB_UART_CDC is now ICE_USB_UARTx_CDC with 'x' the UART number
#endif

#ifdef ICE_USB_UART_NUM
#error ICE_USB_UART_NUM is now implicit, no need to define it
#endif

#ifdef ICE_USB_USE_DEFAULT_CDC
#error ICE_USB_USE_DEFAULT_CDC is now implicit, no need to define it
#endif

#ifdef ICE_USB_USE_DEFAULT_DFU
#error ICE_USB_USE_DEFAULT_DFU is now implicit, no need to define it
#endif

#define WATCHDOG_DELAY 3000

#define DFU_ALT_CRAM 0
#define DFU_ALT_FLASH 1

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

#ifdef ICE_USB_UART0_CDC
static void ice_usb_cdc_to_uart0(uint8_t byte) {
    if (uart_is_writable(uart0)) {
        uart_putc(uart0, byte);
    }
}
static void ice_usb_uart0_to_cdc(void) {
    while (uart_is_readable(uart0)) {
        uint8_t byte = uart_getc(uart0);
        tud_cdc_n_write_char(ICE_USB_UART0_CDC, byte);
        tud_cdc_n_write_flush(ICE_USB_UART0_CDC);
    }
}
#endif

#ifdef ICE_USB_UART1_CDC
static void ice_usb_cdc_to_uart1(uint8_t byte) {
    if (uart_is_writable(uart1)) {
        uart_putc(uart1, byte);
    }
}
static void ice_usb_uart1_to_cdc(void) {
    while (uart_is_readable(uart1)) {
        uint8_t byte = uart_getc(uart1);
        tud_cdc_n_write_char(ICE_USB_UART1_CDC, byte);
        tud_cdc_n_write_flush(ICE_USB_UART1_CDC);
    }
}
#endif

#ifdef ICE_USB_SPI_CDC
static void ice_usb_cdc_to_spi(uint8_t byte) {
    static enum { GET_COMMAND, GET_DATA, GET_EXTENDED } state;
    static size_t buf_len, buf_i, i;
    static char buf[128];

    printf("i=%d state=%d", i++, state);

    switch (state) {

    // The next byte is a command byte: [1*ReadWriteIndicator, 7*DataLength]
    case GET_COMMAND:

        // Special case (null read): deselects the SPI peripheral
        if (byte == 0x00) {
            ice_spi_chip_deselect(ICE_SRAM_CS_PIN);
            state = GET_COMMAND;

        // Special case (null write): extended command
        } else if (byte == 0x80) {
            state = GET_EXTENDED;
    
        // First bit high: forward SPI data to USB
        } else if (byte >> 7 == 1) {
            uint8_t len = byte & 0b01111111;

            ice_spi_chip_select(ICE_SRAM_CS_PIN);
            ice_spi_read_blocking(buf, len);
            tud_cdc_n_write(ICE_USB_SPI_CDC, buf, len);
            tud_cdc_n_write_flush(ICE_USB_SPI_CDC);
            state = GET_COMMAND;

        // First bit low: forward USB data to SPI
        } else if (byte >> 7 == 0) {
            ice_spi_chip_select(ICE_SRAM_CS_PIN);
            buf_len = byte & 0b01111111;
            state = GET_DATA;
        }
        break;

    // Read one extended command byte (ignored for now)
    case GET_EXTENDED:
        state = GET_COMMAND;
        break;

    // Take as many bytes as the amount specified during GET_COMMAND
    case GET_DATA:
        buf[buf_i++] = byte;
        if (buf_i == buf_len) {
            ice_spi_write_blocking(buf, buf_len);
            buf_len = 0;
            buf_i = 0;
            state = GET_COMMAND;
        }
        break;
    }

    printf(" next=%d byte=0x%02X buf_len=%d buf_i=%d\r\n",
        state, byte, buf_len, buf_i);
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
void ice_usb_cdc_to_fpga(uint8_t byte) {
    ice_wishbone_serial(byte);
}
#endif

void (*tud_cdc_rx_cb_table[CFG_TUD_CDC])(uint8_t) = {
#ifdef ICE_USB_UART0_CDC
    [ICE_USB_UART0_CDC] = &ice_usb_cdc_to_uart0,
#endif
#ifdef ICE_USB_UART1_CDC
    [ICE_USB_UART1_CDC] = &ice_usb_cdc_to_uart1,
#endif
#ifdef ICE_USB_FPGA_CDC
    [ICE_USB_FPGA_CDC] = &ice_usb_cdc_to_fpga,
#endif
#ifdef ICE_USB_SPI_CDC
    [ICE_USB_SPI_CDC] = &ice_usb_cdc_to_spi,
#endif
};

#if ICE_USB_UART0_CDC || ICE_USB_UART1_CDC || ICE_USB_FPGA_CDC || ICE_USB_SPI_CDC
void tud_cdc_rx_cb(uint8_t cdc_num) {
    // existing callback for that CDC number, send it all available data
    assert(cdc_num < sizeof(tud_cdc_rx_cb_table) / sizeof(*tud_cdc_rx_cb_table));

    while (tud_cdc_n_available(cdc_num)) {
        uint8_t byte = tud_cdc_n_read_char(cdc_num);
        if (tud_cdc_rx_cb_table[cdc_num] != NULL) {
            tud_cdc_rx_cb_table[cdc_num](byte);
        }
    }
}
#endif

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
        //ice_spi_wait_completion();

        // Disable all interrupts except USB.
        irq_set_mask_enabled(~(1 << USBCTRL_IRQ), false);

        // Soft reset core 1.
        // TODO: if we get unlucky, core 1 might reset while holding a TinyUSB lock, in which case DFU download might hang.
        multicore_reset_core1();

        // Keep running if flashing from SRAM
        if (alt != DFU_ALT_CRAM) {
            // Ensure eventual reboot in case user doesn't pass -R to dfu-util
            watchdog_enable(WATCHDOG_DELAY, true /* pause_on_debug */);
        }

        // make sure the RP2040 have full access to the bus
        ice_fpga_stop();
        ice_spi_init();

        if (alt == DFU_ALT_CRAM) {
            ice_cram_open();
        }
        if (alt == DFU_ALT_FLASH) {
            ice_flash_init();
        }
    }

    watchdog_update();

    uint32_t dest_addr = block_num * CFG_TUD_DFU_XFER_BUFSIZE;

    for (uint32_t offset = 0; offset < length; offset += ICE_FLASH_PAGE_SIZE) {
        if (alt == DFU_ALT_CRAM) {
            ice_cram_write(data, length);
        }
        if (alt == DFU_ALT_FLASH) {
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

    if (alt == DFU_ALT_CRAM) {
        fpga_done = ice_cram_close();
    }
    if (alt == DFU_ALT_FLASH) {
        fpga_done = ice_fpga_start();
    }

    tud_dfu_finish_flashing(fpga_done ? DFU_STATUS_OK : DFU_STATUS_ERR_FIRMWARE);
}

// Called if -R option passed to dfu-util.
void tud_dfu_detach_cb(void) {
    watchdog_reboot(0, 0, 0);
}

// Init everything as declared in <tusb_config.h>
void ice_usb_init(void) {
    tusb_init();

#ifdef ICE_USB_UART0_CDC
    irq_set_exclusive_handler(UART0_IRQ, ice_usb_uart0_to_cdc);
    irq_set_enabled(UART0_IRQ, true);
    uart_set_irq_enables(uart0, true, false);
#endif

#ifdef ICE_USB_UART1_CDC
    irq_set_exclusive_handler(UART1_IRQ, ice_usb_uart1_to_cdc);
    irq_set_enabled(UART1_IRQ, true);
    uart_set_irq_enables(uart1, true, false);
#endif

#ifdef ICE_USB_SPI_CDC
    ice_sram_init();
    ice_spi_init();
#endif

#ifdef ICE_USB_USE_TINYUF2_MSC
    board_init();
    uf2_init();
#endif
}
