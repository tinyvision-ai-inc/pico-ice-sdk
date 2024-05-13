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

/**
 * @defgroup ice_usb
 * @brief TinyUSB and TinyUF2 configuration
 * @{
 *
 * The [pico-ice-sdk](https://github.com/tinyvision-ai-inc/pico-ice-sdk/)
 * makes use of the [pico-sdk](https://github.com/raspberrypi/pico-sdk/) which
 * uses the [TinyUSB](https://github.com/hathach/tinyusb) library for providing
 * USB device mode and host mode.
 *
 * "ice_usb" comes as a separate "pico_ice_usb" library to
 * [add in the CMakeLists.txt](https://github.com/tinyvision-ai-inc/pico-ice-sdk/blob/develop/examples/pico_usb_uart/CMakeLists.txt#L21).
 *
 * The library user needs to provide `tusb_config.h` and `usb_descriptors.c`.
 * Examples listed [below](#examples).
 * tud_task() needs to be called frequently in the firmware.
 *
 *
 * ## USB CDC: USB UART forwarding.
 *
 * The pico-ice-sdk allows to configure forwarding from an USB CDC interface to an
 * UART interface with the two defines below:
 *
 * To enable:
 * 1. Define `ICE_USB_UART0_CDC` or `ICE_USB_UART1_CDC` to the CDC interface number to use.
 * 2. Adjust these as needed:
 *    [`ITF_NUM_CDCx`](https://github.com/tinyvision-ai-inc/pico-ice-sdk/blob/main/examples/pico_usb_uart/usb_descriptors.c#L30),
 *    [`ITF_NUM_DATAx`](https://github.com/tinyvision-ai-inc/pico-ice-sdk/blob/main/examples/pico_usb_uart/usb_descriptors.c#L30),
 *    [`CFG_TUD_CDC`](https://github.com/tinyvision-ai-inc/pico-ice-sdk/blob/main/examples/pico_usb_uart/tusb_config.h#L44),
 *    [`TUD_CDC_DESCRIPTOR`](https://github.com/tinyvision-ai-inc/pico-ice-sdk/blob/main/examples/pico_usb_uart/usb_descriptors.c#L38),
 *    [`STRID_CDC+x`](https://github.com/tinyvision-ai-inc/pico-ice-sdk/blob/main/examples/pico_usb_uart/usb_descriptors.c#L49)
 *
 * See the
 * [`pico_usb_uart`](https://github.com/tinyvision-ai-inc/pico-ice-sdk/tree/main/examples/pico_usb_uart/)
 * example.
 *
 *
 * ## USB SPI: FPGA/SRAM/flash forwarding
 *
 * The pico-ice-sdk allows to configure forwarding data between an USB CDC interface and the main SPI interface around which everything is hooked-up together.
 * This allows to exchange data with the iCE40, SRAM and flash directly from USB.
 * To do so, a very small protocol was added on op of USB-CDC to control SPI:
 *
 * When wanting to write `\x31\x32\x33\x34\x35` over SPI, the I/O over USB-CDC would be:
 * ```
 * TX: -<0x05 0x31 0x32 0x33 0x34 0x35 0x00>-
 * RX: --------------------------------------
 *       WR*5   D1   D2   D3   D4   D5  END
 * ```
 *
 * When trying to read 4 bytes from SPI, the I/O over USB-CDC would be:
 * ```
 * TX: -<0x84>-----------------------<0x00>-
 * RX: --------<0x00 0x00 0x00 0x00>--------
 *       RD*4    D1   D2   D3   D4    END
 * ```
 *
 * To change to a different SPI chip select pin, the I/O over USB-CDC would be:
 * ```
 * TX: -<0x80 0x00>- or -<0x80 0x01>- or -<0x80 0x02>-
 * RX: -------------    -------------    -------------
 *       CMD  FPGA        CMD  SRAM        CMD  FLASH
 * ```
 *
 * You can use this python library:
 * [`pico_ice_spi.py`](https://github.com/tinyvision-ai-inc/pico-ice-sdk/blob/main/examples/pico_usb_spi/pico_ice_spi.py)
 *
 * To enable:
 * 1. Define `ICE_USB_SPI_CDC` to the CDC interface number to use.
 * 2. Adjust these as needed:
 *    [`ITF_NUM_CDCx`](https://github.com/tinyvision-ai-inc/pico-ice-sdk/blob/main/examples/pico_usb_spi/usb_descriptors.c#L30),
 *    [`ITF_NUM_DATAx`](https://github.com/tinyvision-ai-inc/pico-ice-sdk/blob/main/examples/pico_usb_spi/usb_descriptors.c#L30),
 *    [`CFG_TUD_CDC`](https://github.com/tinyvision-ai-inc/pico-ice-sdk/blob/main/examples/pico_usb_spi/tusb_config.h#L44),
 *    [`TUD_CDC_DESCRIPTOR`](https://github.com/tinyvision-ai-inc/pico-ice-sdk/blob/main/examples/pico_usb_spi/usb_descriptors.c#L38),
 *    [`STRID_CDC+x`](https://github.com/tinyvision-ai-inc/pico-ice-sdk/blob/main/examples/pico_usb_spi/usb_descriptors.c#L49)
 *
 * See the
 * [`pico_usb_spi`](https://github.com/tinyvision-ai-inc/pico-ice-sdk/tree/main/examples/pico_usb_spi/)
 * example.
 *
 *
 * ## USB CDC: FPGA forwarding
 *
 * The pico-ice-sdk allows to configure forwarding
 * from the USB CDC interface using the
 * [wishbone-serial](https://wishbone-utils.readthedocs.io/en/latest/wishbone-tool/#serial-bridge) protocol
 * to the FPGA SPI interface using the
 * [wishbone-spi](https://wishbone-utils.readthedocs.io/en/latest/wishbone-tool/#spi-bridge) protocol..
 *
 * To enable:
 * 1. Define `ICE_USB_FPGA_CDC` to the CDC interface number to use.
 * 2. Adjust these as needed:
 *    [`ITF_NUM_CDCx`](https://github.com/tinyvision-ai-inc/pico-ice-sdk/blob/main/examples/pico_usb_uart/usb_descriptors.c#L30),
 *    [`ITF_NUM_DATAx`](https://github.com/tinyvision-ai-inc/pico-ice-sdk/blob/main/examples/pico_usb_uart/usb_descriptors.c#L30),
 *    [`CFG_TUD_CDC`](https://github.com/tinyvision-ai-inc/pico-ice-sdk/blob/main/examples/pico_usb_uart/tusb_config.h#L44),
 *    [`TUD_CDC_DESCRIPTOR`](https://github.com/tinyvision-ai-inc/pico-ice-sdk/blob/main/examples/pico_usb_uart/usb_descriptors.c#L38),
 *    [`STRID_CDC+x`](https://github.com/tinyvision-ai-inc/pico-ice-sdk/blob/main/examples/pico_usb_uart/usb_descriptors.c#L49)
 *
 * See the
 * [`pico_usb_fpga`](https://github.com/tinyvision-ai-inc/pico-ice-sdk/tree/main/examples/pico_usb_fpga/)
 * example.
 *
 *
 * ## USB MSC: TinyUF2
 *
 * The [TinyUF2](https://github.com/adafruit/tinyuf2) library from Adafruit permits to expose an MSC USB storage device, with a fake FAT filesystem.
 * This will allow to copy UF2-formatted files using a drag-and-drop scheme containing a bitstream programmed into the FPGA flash.
 * This means no Zadig driver setup needed on Windows.
 *
 * You would need something like the [`uf2-utils`](https://github.com/tinyvision-ai-inc/uf2-utils) to generate the UF2-formatted files.
 *
 * To enable:
 * 1. Define `ICE_USB_USE_TINYUF2_MSC`
 * 2. Adjust these as needed:
 *    [`ITF_NUM_MSCx`](https://github.com/tinyvision-ai-inc/pico-ice-sdk/blob/main/examples/pico_usb_uart/usb_descriptors.c#L30),
 *    [`CFG_TUD_MSC`](https://github.com/tinyvision-ai-inc/pico-ice-sdk/blob/main/examples/pico_usb_uart/tusb_config.h#L45),
 *    [`TUD_MSC_DESCRIPTOR`](https://github.com/tinyvision-ai-inc/pico-ice-sdk/blob/main/examples/pico_usb_uf2/usb_descriptors.c#L37),
 *    [`STRID_MSC+x`](https://github.com/tinyvision-ai-inc/pico-ice-sdk/blob/main/examples/pico_usb_uf2/usb_descriptors.c#L49)
 *
 * See the
 * [`pico_usb_uf2`](https://github.com/tinyvision-ai-inc/pico-ice-sdk/tree/main/examples/pico_usb_uf2/)
 * example.
 */

#pragma once
#include "tusb.h"
#include "tusb_config.h"
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
void ice_usb_task();

#ifdef __cplusplus
}
#endif

/** @} */
