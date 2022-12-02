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

void init_fpga_comm_spi_dma_interface(void);
void ice_write_fpga_spi_dma(uint32_t dest_addr, const void* src, uint32_t size);
void ice_read_fpga_spi_dma(void* dest, uint32_t src_addr, uint32_t size);

/** @} */
#endif
