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
#include "pico/bootrom.h"
#include "pico/multicore.h"
#include "pico/stdlib.h"

// tinyusb
#include "tusb.h"

// pico-ice-sdk
#include "boards/pico_ice.h"
#include "ice_usb.h"
#include "ice_flash.h"
#include "ice_cram.h"
#include "ice_sram.h"
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

#define DFU_ALT_FLASH 0
#define DFU_ALT_CRAM 1

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
void ice_usb_sleep_ms(uint32_t ms)
{
    while (ms-- > 0) {
        ice_usb_task();
        sleep_ms(1);
    }
}

// Invoked when received GET DEVICE DESCRIPTOR
// Application return pointer to descriptor
uint8_t const *tud_descriptor_device_cb(void)
{
    return (uint8_t const *)&tud_desc_device;
}

const uint8_t *tud_descriptor_configuration_cb(uint8_t index)
{
    (void)index;
    return tud_desc_configuration;
}

// Invoked when received GET STRING DESCRIPTOR request
// Application return pointer to descriptor, whose contents must exist long enough for transfer to complete
uint16_t const *tud_descriptor_string_cb(uint8_t index, uint16_t langid)
{
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

static void ice_usb_cdc_to_uart0(uint8_t byte)
{
    if (uart_is_writable(uart0)) {
        uart_putc(uart0, byte);
    }
}

static void ice_usb_uart0_to_cdc(void)
{
    while (uart_is_readable(uart0)) {
        uint8_t byte = uart_getc(uart0);
        tud_cdc_n_write_char(ICE_USB_UART0_CDC, byte);
    }
}

#endif

#ifdef ICE_USB_UART1_CDC

static void ice_usb_cdc_to_uart1(uint8_t byte)
{
    if (uart_is_writable(uart1)) {
        uart_putc(uart1, byte);
    }
}

char uart1_rx_buf[CFG_TUD_CDC_TX_BUFSIZE];
int uart1_rx_index_r;
long long uart1_rx_read_total;
int uart1_rx_index_w;
long long uart1_rx_written_total;

static void ice_usb_uart1_to_cdc(void)
{
    while (uart_is_readable(uart1)) {
        uint8_t byte = uart_getc(uart1);

        uart1_rx_buf[uart1_rx_index_w++] = byte;
        while (uart1_rx_index_w == CFG_TUD_CDC_TX_BUFSIZE)
            uart1_rx_index_w -= CFG_TUD_CDC_TX_BUFSIZE;
        uart1_rx_written_total++;
    }
}

#endif

#ifdef ICE_USB_SPI_CDC

static void ice_usb_cdc_to_spi(uint8_t ch)
{
    static enum { GET_COMMAND, GET_DATA, GET_EXTENDED } state;
    static size_t buf_len, buf_i, pkt;
    static char buf[128];
    static uint8_t csn_pin = ICE_FPGA_CSN_PIN;

    switch (state) {

    // The next byte is a command byte: [1*ReadWriteIndicator, 7*DataLength]
    case GET_COMMAND:

        // Chip deselect
        if (ch == 0x00) {
            ice_spi_chip_deselect(csn_pin);
            state = GET_COMMAND;

        // Extended command
        } else if (ch == 0x80) {
            state = GET_EXTENDED;

        // Read [num]
        } else if (ch >> 7 == 1) {
            ice_spi_chip_select(csn_pin);
            buf_len = ch & 0b01111111;
            ice_spi_read_blocking(buf, buf_len);
            tud_cdc_n_write(ICE_USB_SPI_CDC, buf, buf_len);
            tud_cdc_n_write_flush(ICE_USB_SPI_CDC);
            state = GET_COMMAND;

        // Write [num]
        } else if (ch >> 7 == 0) {
            ice_spi_chip_select(csn_pin);
            buf_len = ch & 0b01111111;
            state = GET_DATA;
        }
        break;

    // Read one extended command byte (ignored for now)
    case GET_EXTENDED:
        switch (ch) {
        case 0x00:
            csn_pin = ICE_FPGA_CSN_PIN;
            break;
        case 0x01:
            csn_pin = ICE_SRAM_CS_PIN;
            break;
        case 0x02:
            csn_pin = ICE_FLASH_CSN_PIN;
            break;
        }
        state = GET_COMMAND;
        break;

    // Take as many bytes as the amount specified during GET_COMMAND
    case GET_DATA:
        buf[buf_i++] = ch;
        if (buf_i == buf_len) {
            ice_spi_write_blocking(buf, buf_len);
            buf_len = 0;
            buf_i = 0;
            state = GET_COMMAND;
        }
        break;
    }
}

#endif

#ifdef ICE_USB_FPGA_CDC

void ice_wishbone_serial_tx_cb(uint8_t byte)
{
    tud_cdc_n_write_char(ICE_USB_FPGA_CDC, byte);
    tud_cdc_n_write_flush(ICE_USB_FPGA_CDC);
}

void ice_wishbone_serial_read_cb(uint32_t addr, uint8_t *buf, size_t size)
{
    ice_fpga_read(addr, buf, size);
}

void ice_wishbone_serial_write_cb(uint32_t addr, uint8_t *buf, size_t size)
{
    ice_fpga_write(addr, buf, size);
}

void ice_usb_cdc_to_fpga(uint8_t byte)
{
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

void tud_cdc_line_coding_cb(uint8_t itf, cdc_line_coding_t const *coding)
{
    printf("%s: coding=%p baud=%d\n", __func__, coding, coding->bit_rate);

    /* Mimick the Arduino reboot signal:
     * https://arduino.github.io/arduino-cli/dev/platform-specification/#1200-bps-bootloader-reset */
    if (coding->bit_rate == 1200) {
        reset_usb_boot(0, 0);
        assert(!"not reached");
    }

    switch (itf) {
#ifdef ICE_USB_UART0_CDC
    case ICE_USB_UART0_CDC:
        uart_set_baudrate(uart0, coding->bit_rate);
        break;
#endif
#ifdef ICE_USB_UART1_CDC
    case ICE_USB_UART1_CDC:
        uart_set_baudrate(uart1, coding->bit_rate);
        break;
#endif
    }
}

void tud_cdc_rx_cb(uint8_t cdc_num)
{
    // existing callback for that CDC number, send it all available data
    assert(cdc_num < sizeof(tud_cdc_rx_cb_table) / sizeof(*tud_cdc_rx_cb_table));

    if (tud_cdc_rx_cb_table[cdc_num] == NULL) {
        return;
    }
    for (int32_t ch; (ch = tud_cdc_n_read_char(cdc_num)) >= 0;) {
        tud_cdc_rx_cb_table[cdc_num](ch);
    }
}

#endif

// Invoked right before tud_dfu_download_cb() (state=DFU_DNBUSY) or tud_dfu_manifest_cb() (state=DFU_MANIFEST)
// Application return timeout in milliseconds (bwPollTimeout) for the next download/manifest operation.
// During this period, USB host won't try to communicate with us.
uint32_t tud_dfu_get_timeout_cb(uint8_t alt, uint8_t state)
{
    return 0; // Request we are polled in 1ms
}

static bool dfu_ongoing;

void dfu_init(uint8_t alt)
{
    ice_spi_init();

    switch (alt) {
    case DFU_ALT_CRAM:
        ice_cram_open();
        break;
    case DFU_ALT_FLASH:
        // Make sure the RP2040 have full access to the SPI bus
        ice_fpga_stop();

        ice_flash_init();

        // Ensure reboot in case user doesn't pass -R to dfu-util
        watchdog_enable(WATCHDOG_DELAY, true /* pause_on_debug */);

        // Soft reset core 1.
        // TODO: if we get unlucky, core 1 might reset while holding a TinyUSB
        // lock, in which case DFU download might hang.
        multicore_reset_core1();

        // Disable all interrupts except USB and DMA (needed for flash program)
        irq_set_mask_enabled(~((1 << USBCTRL_IRQ) | (1 << DMA_IRQ_1)), false);
        break;
    }
}

// Invoked when received DFU_DNLOAD (wLength>0) following by DFU_GETSTATUS (state=DFU_DNBUSY) requests
// This callback could be returned before flashing op is complete (async).
// Once finished flashing, application must call tud_dfu_finish_flashing()
void tud_dfu_download_cb(uint8_t alt, uint16_t block_num, const uint8_t *data, uint16_t length)
{
    uint32_t addr;

    ice_spi_wait_completion();

    if (!dfu_ongoing) {
        dfu_init(alt);
        dfu_ongoing = true;
    }

    addr = block_num * CFG_TUD_DFU_XFER_BUFSIZE;
    for (uint32_t i = 0; i < length; i += ICE_FLASH_PAGE_SIZE) {
        switch (alt) {
        case DFU_ALT_CRAM:
            ice_cram_write(data, length);
            break;
        case DFU_ALT_FLASH:
            watchdog_update();

            if ((addr + i) % ICE_FLASH_SECTOR_SIZE == 0) {
                ice_flash_erase_sector(addr + i);
            }
            ice_flash_program_page(addr + i, data + i);
            break;
        }
    }

    tud_dfu_finish_flashing(DFU_STATUS_OK);

    while (dfu_ongoing) {
        tud_task();
    }
}

// Invoked when download process is complete, received DFU_DNLOAD (wLength=0)
// following by DFU_GETSTATUS (state=Manifest) Application can do checksum, or
// actual flashing if buffered entire image previously.
// Once finished flashing, application must call tud_dfu_finish_flashing()
void tud_dfu_manifest_cb(uint8_t alt)
{
    bool ok;

    switch (alt) {
    case DFU_ALT_CRAM:
        ok = ice_cram_close();
        break;
    case DFU_ALT_FLASH:
        ok = ice_fpga_start();
        break;
    }

    tud_dfu_finish_flashing(ok ? DFU_STATUS_OK : DFU_STATUS_ERR_FIRMWARE);

    dfu_ongoing = false;
}

// Called if -R option passed to dfu-util.
void tud_dfu_detach_cb(void)
{
    watchdog_reboot(0, 0, 0);
}

// Init everything as declared in <tusb_config.h>
void ice_usb_init(void)
{
    tusb_init();

    // This is a blocking call, but expected to be done once at initialization
    // rather than in the main loop.
    while (!tud_ready()) {
        tud_task();
    }

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
    ice_spi_init_cs_pin(ICE_SRAM_CS_PIN, true);
    ice_spi_init_cs_pin(ICE_FLASH_CSN_PIN, false);
    ice_spi_init_cs_pin(ICE_FPGA_CSN_PIN, false);
    ice_spi_init();
#endif

#ifdef ICE_USB_USE_TINYUF2_MSC
    board_init();
    uf2_init();
#endif
}

// Task function should be called in main/rtos loop
// this additionally flushes uart buffers
void ice_usb_task() {
    tud_task();

#ifdef ICE_USB_UART0_CDC
    tud_cdc_n_write_flush(ICE_USB_UART0_CDC);
#endif

#ifdef ICE_USB_UART1_CDC
    uart1_rx_read_total = MAX(uart1_rx_read_total, uart1_rx_written_total - CFG_TUD_CDC_TX_BUFSIZE);

    while (uart1_rx_read_total < uart1_rx_written_total) {
        char byte = uart1_rx_buf[uart1_rx_index_r++];
        while (uart1_rx_index_r == CFG_TUD_CDC_TX_BUFSIZE)
            uart1_rx_index_r -= CFG_TUD_CDC_TX_BUFSIZE;
        uart1_rx_read_total++;

        if (tud_cdc_n_write_available(ICE_USB_UART1_CDC) > 0)
            tud_cdc_n_write_char(ICE_USB_UART1_CDC, byte);
    }

    tud_cdc_n_write_flush(ICE_USB_UART1_CDC);
#endif
}
