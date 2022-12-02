#ifndef ICE_SSRAM_H
#define ICE_SSRAM_H
/**
 * Low-level API for reading and writing to the FPGA using SPI DMA for minimum overhead.
 * @defgroup pico_ice_fpga_comm
 * @{
 */

#include <stdint.h>
#include <stddef.h>
#include "boards/pico_ice.h"

void init_fpga_comm_interface(void);
void write_fpga(uint32_t dest_addr, const void* src, uint32_t size);
void read_fpga(void* dest, uint32_t src_addr, uint32_t size);

/** @} */
#endif
