/** Low-level API for communicating with serial memory chips: reading and writing.
* \defgroup pico_ice_ssram
*/

#ifndef _ICE_SSRAM_H
#define _ICE_SSRAM_H

#define ICE_SSRAM_STATUS_BUSY_MASK  0x01
#define ICE_SSRAM_FLASH_PAGE_SIZE   0x100

#include <stdint.h>
#include <stddef.h>
#include "boards/pico_ice.h"

typedef void (*ice_ssram_async_callback_t)(void);

// Common interface
void ice_ssram_init(int bit_rate, int irq /* -1 for synchronous mode */);
void ice_ssram_deinit(void);
bool ice_ssram_is_async_complete(void);
void ice_ssram_await_async_completion(void);
void ice_ssram_set_async_callback(ice_ssram_async_callback_t callback);

// Higher level interface
uint8_t ice_ssram_get_status(int cs_pin);
void ice_ssram_erase_chip(int cs_pin);
void ice_ssram_erase_sector(int cs_pin, uint32_t dest_addr);
void ice_ssram_enable_write(int cs_pin, bool enabled);
void ice_ssram_write(int cs_pin, uint32_t dest_addr, const void* src, uint32_t size);
void ice_ssram_write_async(int cs_pin, uint32_t dest_addr, const void* src, uint32_t size);
void ice_ssram_read(int cs_pin, void* dest, uint32_t src_addr, uint32_t size);
void ice_ssram_read_async(int cs_pin, void* dest, uint32_t src_addr, uint32_t size);
void ice_ssram_enable_power(int cs_pin, bool enabled);

// Lower level interface
void ice_ssram_output_command(int cs_pin,
                              const uint8_t* command, uint32_t command_size,
                              const void* data, uint32_t data_size,
                              bool async);
void ice_ssram_input_command(int cs_pin,
                             const uint8_t* command, uint32_t command_size,
                             void* data, uint32_t data_size,
                             bool async);

#endif
