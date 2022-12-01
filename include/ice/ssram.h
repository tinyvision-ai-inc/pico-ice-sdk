#ifndef ICE_SSRAM_H
#define ICE_SSRAM_H
/**
 * Low-level API for communicating with flash chips: reading and writing.
 * @defgroup pico_ice_ssram
 * @{
 */

/*
 * Most of the code in this example is contributed by z80. Thank you!
 */
#include <stdint.h>
#include <stddef.h>
#include "boards/pico_ice.h"

void init_serial_memory_interface(void);
void write_serial_memory(uint32_t dest_addr, const void* src, uint32_t size);
void read_serial_memory(void* dest, uint32_t src_addr, uint32_t size);

/** @} */
#endif
