#ifndef ICE_SMEM_H
#define ICE_SMEM_H

#include <stdint.h>
#include <stddef.h>
#include "boards/pico_ice.h"

#ifdef __cplusplus
extern "C" {
#endif

// This module is _not_ thread safe.

#define ICE_SMEM_STATUS_BUSY_MASK  0x01
#define ICE_SMEM_FLASH_PAGE_SIZE   0x100

void ice_smem_init(uint baudrate, int irq);
void ice_smem_deinit(void);
bool ice_smem_is_async_complete(void);
void ice_smem_await_async_completion(void);
uint8_t ice_smem_get_status(uint cs_pin);
void ice_smem_erase_chip(uint cs_pin);
void ice_smem_erase_sector(uint cs_pin, uint32_t dest_addr);
void ice_smem_enable_write(uint cs_pin);
void ice_smem_disnable_write(uint cs_pin);
void ice_smem_write(uint cs_pin, uint32_t dest_addr, const void *src, uint32_t size);
void ice_smem_read(uint cs_pin, void *dest, uint32_t src_addr, uint32_t size);
void ice_smem_power_on(uint cs_pin);
void ice_smem_power_off(uint cs_pin);
void ice_smem_write_async(uint cs_pin, uint32_t dest_addr, const void *src, uint32_t size,
                          void (*callback)(void *), void *context);
void ice_smem_read_async(uint cs_pin, void *dest, uint32_t src_addr, uint32_t size,
                          void (*callback)(void *), void *context);
void ice_smem_output_command(uint cs_pin,
                             const uint8_t *command, uint32_t command_size,
                             const void *data, uint32_t data_size);
void ice_smem_output_command_async(uint cs_pin,
                                   const uint8_t *command, uint32_t command_size,
                                   const void *data, uint32_t data_size,
                                   void (*callback)(void *), void *context);
void ice_smem_input_command(uint cs_pin,
                            const uint8_t *command, uint32_t command_size,
                            void *data, uint32_t data_size);
void ice_smem_input_command_async(uint cs_pin,
                                  const uint8_t *command, uint32_t command_size,
                                  void *data, uint32_t data_size,
                                  void (*callback)(void *), void *context);

#ifdef __cplusplus
}
#endif

#endif
