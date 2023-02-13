#ifndef ICE_FPGA_H
#define ICE_FPGA_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

void ice_fpga_init(uint8_t frequency_mhz);
bool ice_fpga_start(void);
void ice_fpga_stop(void);

#ifdef __cplusplus
}
#endif

#endif
