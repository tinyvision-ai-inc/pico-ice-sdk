#ifndef ICE_FPGA_BITSTREAM_H
#define ICE_FPGA_BITSTREAM_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

void ice_bitstream_open(void);
void ice_bitstream_write(const uint8_t *bitstream, uint32_t size);
bool ice_bitstream_close(void);

#ifdef __cplusplus
}
#endif

#endif

