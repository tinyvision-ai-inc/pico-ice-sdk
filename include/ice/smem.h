/** Low-level API for communicating with serial memory chips: reading and writing.
* \defgroup pico_ice_smem
*/

#ifndef _ICE_SMEM_H
#define _ICE_SMEM_H

#define ICE_SMEM_STATUS_BUSY_MASK  0x01
#define ICE_SMEM_FLASH_PAGE_SIZE   0x100

#include <stdint.h>
#include <stddef.h>
#include "boards/pico_ice.h"

// This module is _not_ thread safe.

typedef void (*ice_smem_async_callback_t)(void* context);

// Common interface
void ice_smem_init(int bit_rate, int irq /* -1 for synchronous mode */);
void ice_smem_deinit(void);
bool ice_smem_is_async_complete(void);
void ice_smem_await_async_completion(void);

// Higher level interface
uint8_t ice_smem_get_status(int cs_pin);
void ice_smem_erase_chip(int cs_pin);
void ice_smem_erase_sector(int cs_pin, uint32_t dest_addr);
void ice_smem_enable_write(int cs_pin, bool enabled);
void ice_smem_write(int cs_pin, uint32_t dest_addr, const void* src, uint32_t size);
void ice_smem_read(int cs_pin, void* dest, uint32_t src_addr, uint32_t size);
void ice_smem_enable_power(int cs_pin, bool enabled);

void ice_smem_write_async(int cs_pin, uint32_t dest_addr, const void* src, uint32_t size,
                          ice_smem_async_callback_t callback, void* context);

void ice_smem_read_async(int cs_pin, void* dest, uint32_t src_addr, uint32_t size,
                          ice_smem_async_callback_t callback, void* context);

// Lower level interface
void ice_smem_output_command(int cs_pin,
                             const uint8_t* command, uint32_t command_size,
                             const void* data, uint32_t data_size);

void ice_smem_output_command_async(int cs_pin,
                                   const uint8_t* command, uint32_t command_size,
                                   const void* data, uint32_t data_size,
                                   ice_smem_async_callback_t callback, void* context);

void ice_smem_input_command(int cs_pin,
                            const uint8_t* command, uint32_t command_size,
                            void* data, uint32_t data_size);

void ice_smem_input_command_async(int cs_pin,
                                  const uint8_t* command, uint32_t command_size,
                                  void* data, uint32_t data_size,
                                  ice_smem_async_callback_t callback, void* context);

#endif
