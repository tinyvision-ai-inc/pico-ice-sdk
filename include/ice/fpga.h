#ifndef ICE_FPGA_H
#define ICE_FPGA_H
#include <stdint.h>
#include "boards/pico_ice.h"

/**
 * Low-level API for interacting with the FPGA chip.
 * @defgroup pico_ice_fpga
 * @{
 */

void ice_fpga_init_clock(uint8_t mhz);
void ice_fpga_init_uart(uint32_t mhz);
void ice_fpga_init(void);

/** @} */
#endif
