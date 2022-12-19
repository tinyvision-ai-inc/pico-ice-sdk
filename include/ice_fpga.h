#ifndef ICE_FPGA_H
#define ICE_FPGA_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

void ice_fpga_init_clock(uint8_t frequency_mhz);
void ice_fpga_init_uart(uint32_t frequency_hz);
void ice_fpga_init(void);
bool ice_fpga_reset(void);
void ice_fpga_halt(void);

#ifdef __cplusplus
}
#endif

#endif
