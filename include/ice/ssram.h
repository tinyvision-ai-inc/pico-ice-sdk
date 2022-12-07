/** Low-level API for communicating with flash chips: reading and writing.
* \defgroup pico_ice_ssram
*/

#ifndef _ICE_SSRAM_H
#define _ICE_SSRAM_H

#include <stdint.h>
#include <stddef.h>
#include "boards/pico_ice.h"

void ice_ssram_init(int irq);
void ice_ssram_deinit(void);
void ice_ssram_write(int cs_pin, uint32_t dest_addr, const void* src, uint32_t size);
void ice_ssram_read(int cs_pin, void* dest, uint32_t src_addr, uint32_t size);
bool ice_ssram_is_busy(void);
void ice_ssram_wait(void);

#endif
