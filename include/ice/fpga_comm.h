/** Low-level API for reading and writing to the FPGA using SPI DMA for minimum overhead.
* \defgroup pico_ice_fpga_comm
*/

#ifndef _ICE_FPGA_COMM_H
#define _ICE_FPGA_COMM_H

#include <stdint.h>
#include <stddef.h>
#include "boards/pico_ice.h"

void ice_fpga_comm_init(void);
void ice_fpga_comm_wait(void);
void ice_fpga_comm_write(uint32_t dest_addr, const void* src, uint32_t size);
void ice_fpga_comm_read(void* dest, uint32_t src_addr, uint32_t size);

#endif
