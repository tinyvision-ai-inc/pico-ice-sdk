#ifndef ICE_USB_H
#define ICE_USB_H
/*
 * USB-related functions.
 * Calling ice_usb_init() is already done by ice_init().
 * ice_usb_task() should be called in the main loop for USB flashing and USB UART support.
 * @defgroup usb
 * @{
 */
#include "boards/pico_ice.h"
#include "tusb.h"

/** TinyUSB CDC interface number for the USB-UART link. */
#define ICE_USB_UART_FPGA_ITF 1

// in src/tinyuf2/uf2.h
void uf2_init(void);
// in src/tinyuf2/board_api.h
void board_init(void);

void ice_usb_init(void);
void ice_usb_task(void);

/** @} */
#endif
