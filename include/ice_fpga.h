#ifndef ICE_FPGA_H
#define ICE_FPGA_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

void ice_init_clock(uint8_t frequency_mhz);
void ice_init(void);
bool ice_reset(void);
void ice_halt(void);

#ifdef __cplusplus
}
#endif

#endif
