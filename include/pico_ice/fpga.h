#ifndef PICO_ICE_FPGA_H
#define PICO_ICE_FPGA_H
#include "boards/pico_ice.h"

/**
 * Low-level API for interacting with the FPGA chip.
 * @defgroup pico_ice_fpga
 * @{
 */

void fpga_init_clock(uint8_t mhz);
void fpga_init_uart(uint32_t mhz);

/** @} */
#endif
