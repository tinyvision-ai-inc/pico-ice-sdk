#pragma once
#include <assert.h>
#include "boards/pico_ice.h"
#include "tusb.h"
#include "bsp/board.h"

/**
 * @brief High-level API for driving the board.
 * It is under heavy development and subject to change at any time!
 */

/**
 * @brief Call all functions below with default values:
 * no need to call any other initialization function when this is called.
 */
void ice_init_defaults(void);

/**
 * @brief Initialise the SPI1 peripheral, dedicated to flashing the FPGA.
 */
void ice_init_flash(void);

/**
 * @brief Initialise the TinyUSB library, enabling the UART (CDC) and
 * drag-and-drop (MSC) interfaces.
 */
void ice_init_usb(void);

/**
 * @brief Initialise the FPGA chip and communication with it.
 * This will start the FPGA clock and take it out of reset.
 */
void ice_init_fpga(void);

/**
 * @brief Run all code related to USB in a non-blocking way.
 * It is typically to be placed at the end of the main application loop.
 */
void ice_usb_task(void);
