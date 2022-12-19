#ifndef _ICE_FPGA_COMM_H
#define _ICE_FPGA_COMM_H

#include <stdint.h>
#include <stddef.h>
#include "boards/pico_ice.h"

#ifdef __cplusplus
extern "C" {
#endif

void ice_fpga_comm_init(void);
void ice_fpga_comm_write(uint32_t dest_addr, const void* src, uint32_t size);
void ice_fpga_comm_read_(void* dest, uint32_t src_addr, uint32_t size);

#ifdef __cplusplus
}
#endif

#endif
