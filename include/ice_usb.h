#pragma once
#include "tusb.h"
#include "pico/unique_id.h"

// Predefined macros to avoid repetitive
#define USB_VID 0x1209      // InterBiometrics - https://pid.codes/
#define USB_PID 0xB1C0      // Reserved for pico-ice - https://github.com/pidcodes/pidcodes.github.com/pull/801/files
#define USB_MANUFACTURER    "tinyVision.ai Inc."
#define USB_PRODUCT         "pico-ice"
#define USB_LANG_EN         (const char[]){ 0x09, 0x04 }
#define USB_VENDOR          "TinyVision.ai Inc"
#define EPOUT               0x00
#define EPIN                0x80

#define CONFIG_TOTAL_LEN    (TUD_CONFIG_DESC_LEN \
    + TUD_CDC_DESC_LEN    * CFG_TUD_CDC \
    + TUD_MSC_DESC_LEN    * CFG_TUD_MSC \
    + TUD_DFU_DESC_LEN(CFG_TUD_DFU_ALT) \
    + TUD_HID_DESC_LEN    * CFG_TUD_HID \
    + TUD_MIDI_DESC_LEN   * CFG_TUD_MIDI \
    + TUD_VENDOR_DESC_LEN * CFG_TUD_VENDOR)

// Generated at random for the pico-ice as advised by https://github.com/microsoft/uf2/
#define ICE_UF2_FAMILY_ID 0x792e7263

// Simplify the declaration of string IDs
enum string_desc {
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

extern char usb_serial_number[PICO_UNIQUE_BOARD_ID_SIZE_BYTES * 2 + 1];

#ifdef __cplusplus
extern "C" {
#endif

void ice_usb_init(void);

#ifdef __cplusplus
}
#endif
