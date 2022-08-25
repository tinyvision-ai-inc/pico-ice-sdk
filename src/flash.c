#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/spi.h"

#define FLASH_CMD_READ	0x03

void
flash_read(spi_inst_t *spi, uint32_t addr, uint8_t *buf, size_t sz)
{
	uint8_t cmds[] = { FLASH_CMD_READ, addr >> 16, addr >> 8, addr };

	spi_write_blocking(spi, cmds, sizeof cmds);
	sleep_us(1);
	spi_read_blocking(spi, 0x00, buf, sz);
	sleep_us(1);
}
