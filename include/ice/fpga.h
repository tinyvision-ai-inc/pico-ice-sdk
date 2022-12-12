/** Low-level API for interacting with the FPGA chip.
* \defgroup pico_ice_fpga
* \{ */

#ifndef ICE_FPGA_H
#define ICE_FPGA_H

#include <stdint.h>
#include <stdbool.h>

void ice_fpga_init_clock(uint8_t mhz);
void ice_fpga_init_uart(uint32_t mhz);
void ice_fpga_init(void);
int ice_fpga_reset(void);
void ice_fpga_halt(void);

/** \} */
#endif
