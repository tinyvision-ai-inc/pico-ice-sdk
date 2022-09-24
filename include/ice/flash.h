#ifndef ICE_FLASH_H
#define ICE_FLASH_H
#include <stdint.h>
#include "boards/pico_ice.h"
#include "hardware/spi.h"

/**
 * Low-level API for communicating with flash chips: reading and writing.
 * @defgroup pico_ice_flash
 * @{
 */

/** The size of the flash */
#define ICE_FLASH_PAGE_SIZE         256

void ice_flash_init(void);
void ice_flash_read(spi_inst_t *spi, uint8_t pin, uint32_t addr, uint8_t *buf, size_t sz);
void ice_flash_program_page(spi_inst_t *spi, uint8_t pin, uint32_t addr, uint8_t const page[ICE_FLASH_PAGE_SIZE]);
void ice_flash_erase_chip(spi_inst_t *spi, uint8_t pin);

/** @} */
#endif
