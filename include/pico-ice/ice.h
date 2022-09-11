#include <assert.h>
#include "pico-ice/ice.h"

/*
 * High-level API for driving the board.
 */

void ice_flash_init(void);
/*
 * Initialise the SPI1 peripheral, dedicated to flashing the FPGA.
 */

void ice_flash_erase(void);
/*
 * Erase the whole FPGA flash memory. Must be called after ice_flash_init().
 */
