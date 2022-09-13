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

void ice_init_fpga_clock(uint8_t mhz);
/*
 * Initialise the FPGA clock at the given frequency.
 *
 * :param mhz: the clock speed in MHz. Valid values: 48MHz, 24MHz, 16MHz 12MHz, 8MHz, 6MHz, 4MHz, 3MHz, 2MHz, 1MHz.
 */
