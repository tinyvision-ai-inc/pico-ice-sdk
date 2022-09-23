#ifndef PICO_ICE_ICE_H
#define PICO_ICE_ICE_H
#include <stdint.h>
#include <assert.h>
#include "boards/pico_ice.h"
#include "tusb.h"
#include "bsp/board.h"

/**
 * High-level API for driving the board.
 * It is under heavy development and subject to change at any time!
 * @defgroup pico_ice
 */

void ice_init_defaults(void);
void ice_init_flash(void);
void ice_init_usb(void);
void ice_init_fpga(void);
void ice_usb_task(void);

/** @} */
#endif
