#pragma once
#include <assert.h>
#include "boards/pico_ice.h"
#include "tusb.h"
#include "bsp/board.h"

/*
 * High-level API for driving the board.
 * It is under heavy development and subject to change at any time!
 */

void ice_init_flash(void);
/*
 * Initialise the SPI1 peripheral, dedicated to flashing the FPGA.
 */


void ice_init_usb(void);
/*
 * Initialise the TinyUSB library, enabling the UART (CDC) and
 * drag-and-drop (MSC) interfaces.
 */
