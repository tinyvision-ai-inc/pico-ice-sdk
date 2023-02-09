#ifndef ICE_USB_H
#define ICE_USB_H

#include "tusb.h"

#ifdef __cplusplus
extern "C" {
#endif

/// TinyUSB CDC interface number for the USB-UART link.
#define ICE_USB_UART_FPGA_ITF 1

// Generated at random for the pico-ice as advised by https://github.com/microsoft/uf2/
#define ICE_UF2_FAMILY_ID 0x792e7263

void ice_usb_init(void);

#ifdef __cplusplus
}
#endif

#endif
