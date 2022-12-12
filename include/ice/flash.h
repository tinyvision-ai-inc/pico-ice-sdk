/** Low-level API for communicating with flash chips: reading and writing.
* \defgroup pico_ice_flash
* \{ */

#ifndef ICE_FLASH_H
#define ICE_FLASH_H

#include <stdint.h>
#include <stddef.h>
#include "pico/stdlib.h"
//#include "hardware/spi.h"

#ifdef __cplusplus
extern "C" {
#endif

/// The size of the flash
#define ICE_FLASH_PAGE_SIZE         256

void ice_flash_init(void);
void ice_flash_deinit(void);
void static ice_flash_wait(void *spi, uint8_t pin);
void ice_flash_read(void *spi, uint8_t pin, uint32_t addr, uint8_t *buf, size_t sz);
void ice_flash_erase_sector(void *spi, uint8_t pin, uint32_t addr);
void ice_flash_program_page(void *spi, uint8_t pin, uint32_t addr, uint8_t const page[ICE_FLASH_PAGE_SIZE]);
void ice_flash_erase_chip(void *spi, uint8_t pin);
void ice_flash_wakeup(void *spi, uint8_t pin);
void ice_flash_sleep(void *spi, uint8_t pin);

#ifdef __cplusplus
}
#endif
/** \} */
#endif
