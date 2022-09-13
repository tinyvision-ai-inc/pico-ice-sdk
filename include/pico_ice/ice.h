#pragma once
#include <assert.h>
#include "boards/pico_ice.h"

/*
 * High-level API for driving the board.
 * It is under heavy development and subject to change at any time!
 */

void ice_init_flash(void);
/*
 * Initialise the SPI1 peripheral, dedicated to flashing the FPGA.
 */
