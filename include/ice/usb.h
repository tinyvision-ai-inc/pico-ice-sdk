/** USB-related functions.
* Calling ice_usb_init() is already done by ice_init().
* ice_usb_task() should be called in the main loop for USB flashing and USB UART support.
* \defgroup pico_ice_usb
* \{ */

#ifndef ICE_USB_H
#define ICE_USB_H

#include "tusb.h"

#ifdef __cplusplus
extern "C" {
#endif

/// TinyUSB CDC interface number for the USB-UART link.
#define ICE_USB_UART_FPGA_ITF 1

void ice_usb_init(void);

#ifdef __cplusplus
}
#endif
/** \} */
#endif
