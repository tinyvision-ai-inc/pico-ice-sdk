#pragma once
#include "hardware/spi.h"

#define FLASH_PAGE_SIZE		256

void flash_read(spi_hw_t *spi, uint32_t addr, uint8_t *buf, size_t sz);
