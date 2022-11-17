#ifndef ICE_FPGA_H
#define ICE_FPGA_H
/**
 * Low-level API for interacting with the FPGA chip.
 * @defgroup pico_ice_fpga
 * @{
 */
#include <stdint.h>
#include <stdbool.h>
#include "boards/pico_ice.h"

void ice_fpga_init_clock(uint8_t mhz);
void ice_fpga_init_uart(uint32_t mhz);
void ice_fpga_init(void);
void ice_fpga_reset(void);

/** @} */
#endif
