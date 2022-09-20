#pragma once
#include "boards/pico_ice.h"
#include "hardware/spi.h"

/**
 * Low-level API for communicating with flash chips: reading and writing.
 */

#define FLASH_PAGE_SIZE         256

/**
 * @brief Communicate to the chip over SPI and read multiple bytes at chosen address onto onto a buffer.
 * @param spi The SPI interface of the RP2040 to use.
 * @param pin The CS GPIO pin of the RP2040 to use.
 * @param addr The address at which the data is read.
 * @param buf The buffer onto which the data read is stored.
 * @param sz The size of ``buf``.
 */
void flash_read(spi_inst_t *spi, uint8_t pin, uint32_t addr, uint8_t *buf, size_t sz);

/**
 * @brief Program a page of the flash chip at the given address.
 * @param spi The SPI interface of the RP2040 to use.
 * @param pin The CS GPIO pin of the RP2040 to use.
 * @param addr The address at which the data is written.
 * @param page The buffer holding the data to be sent to the flash chip, of size ``FLASH_PAGE_SIZE``.
 */
void flash_program_page(spi_inst_t *spi, uint8_t pin, uint32_t addr, uint8_t const page[FLASH_PAGE_SIZE]);

/**
 * @brief Send a command to erase the whole chip.
 * @param spi The SPI interface of the RP2040 to use.
 * @param pin The CS GPIO pin of the RP2040 to use.
 */
void flash_erase_chip(spi_inst_t *spi, uint8_t pin);
