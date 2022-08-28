#pragma once
#include "hardware/spi.h"

#define FLASH_PAGE_SIZE		256
#define spi_flash		spi1

void flash_read(spi_inst_t *spi, uint32_t addr, uint8_t *buf, size_t sz);
void flash_read_page(spi_inst_t *spi, uint32_t addr, uint8_t page[FLASH_PAGE_SIZE]);
void flash_program_page(spi_inst_t *spi, uint32_t addr, uint8_t const page[FLASH_PAGE_SIZE]);
