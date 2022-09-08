#pragma once
#include "hardware/spi.h"

/*
 * API for communicating with flash chips: reading and writing.
 */

#define FLASH_PAGE_SIZE		256

#define spi_fpga_flash		spi1
/*
 * The flash peripheral instance that is connected to the FGPA's flash chip.
 */

#define FLASH_FPGA_SPI_SCK_PIN	2
#define FLASH_FPGA_SPI_TX_PIN	3
#define FLASH_FPGA_SPI_RX_PIN	0
#define FLASH_FPGA_SPI_CSN_PIN	1
/*
 * Pinout between the RP2040 and the FPGA's flash chip.
 * These pins must be set at high-impedance/floating whenever not in use to program the flash chip,
 * to not distrub the FPGA operation, in particular when the FPGA is under initialisation.
 * This is handled by ``ice_flash_program()``.
 *
 * Each pin must be configured as SPI, except the CSN pin, to be set as a GPIO pin.
 */

void flash_read(spi_inst_t *spi, uint8_t pin, uint32_t addr, uint8_t *buf, size_t sz);
/*
 * Communicate to the chip over SPI and read multiple bytes at chosen address onto onto a buffer.
 *
 * :param spi: The SPI interface of the RP2040 to use.
 * :param pin: The CS GPIO pin of the RP2040 to use.
 * :param addr: The address at which the data is read.
 * :param buf: The buffer onto which the data read is stored.
 * :param sz: The size of ``buf``.
 */

void flash_program_page(spi_inst_t *spi, uint8_t pin, uint32_t addr, uint8_t const page[FLASH_PAGE_SIZE]);
/*
 * Program a page of the flash chip at the given address.
 *
 * :param spi: The SPI interface of the RP2040 to use.
 * :param pin: The CS GPIO pin of the RP2040 to use.
 * :param addr: The address at which the data is written.
 * :param page: The buffer holding the data to be sent to the flash chip, of size ``FLASH_PAGE_SIZE``.
 */

void flash_erase_chip(spi_inst_t *spi, uint8_t pin);
/*
 * Send a command to erase the whole chip.
 *
 * :param spi: The SPI interface of the RP2040 to use.
 * :param pin: The CS GPIO pin of the RP2040 to use.
 */
