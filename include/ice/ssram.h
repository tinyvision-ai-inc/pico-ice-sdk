#ifndef ICE_SSRAM_H
#define ICE_SSRAM_H
/**
 * Low-level API for communicating with flash chips: reading and writing.
 * @defgroup pico_ice_ssram
 * @{
 */

#include <stdint.h>
#include <stddef.h>
#include "boards/pico_ice.h"

void ice_serial_mem_init(void);
void ice_serial_mem_write(uint32_t dest_addr, const void* src, uint32_t size);
void ice_serial_mem_read(void* dest, uint32_t src_addr, uint32_t size);
bool ice_serial_mem_is_busy(void);
void ice_serial_mem_wait(void);

/** @} */
#endif
