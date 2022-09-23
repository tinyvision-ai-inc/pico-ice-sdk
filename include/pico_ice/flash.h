#ifndef FLASH_H
#define FLASH_H

#include "boards/pico_ice.h"
#include "hardware/spi.h"

/**
 * Low-level API for communicating with flash chips: reading and writing.
 * @defgroup pico_ice_flash
 * @{
 */

/** The size of the flash */
#define FLASH_PAGE_SIZE         256

void flash_read(spi_inst_t *spi, uint8_t pin, uint32_t addr, uint8_t *buf, size_t sz);
void flash_program_page(spi_inst_t *spi, uint8_t pin, uint32_t addr, uint8_t const page[FLASH_PAGE_SIZE]);
void flash_erase_chip(spi_inst_t *spi, uint8_t pin);

/** @} */
#endif
