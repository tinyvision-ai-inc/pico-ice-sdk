#include <stdint.h>
#include "pico/stdlib.h"
#include "hardware/structs/spi.h"
#include "hardware/spi.h"
#include "pico-ice/flash.h"

#define FLASH_CMD_PROGRAM_PAGE	0x02
#define FLASH_CMD_READ		0x03
#define FLASH_CMD_ENABLE_WRITE	0x06
#define FLASH_CMD_STATUS	0x05
#define FLASH_CMD_CHIP_ERASE	0xC7

#define FLASH_STATUS_BUSY_MASK	0x01

static void
flash_chip_select(uint8_t pin)
{
	sleep_us(1);
	gpio_put(pin, false);
	sleep_us(1);
}

static void
flash_chip_deselect(uint8_t pin)
{
	sleep_us(1);
	gpio_put(pin, true);
	sleep_us(1);
}

static void
flash_wait(spi_inst_t *spi, uint8_t pin)
{
	uint8_t cmds[] = { FLASH_CMD_STATUS, 0 };
	uint8_t buf[2];

	do {
		flash_chip_select(pin);
		spi_write_read_blocking(spi, cmds, buf, 2);
		flash_chip_deselect(pin);
	} while (buf[0] & FLASH_STATUS_BUSY_MASK);
}

static void
flash_enable_write(spi_inst_t *spi, uint8_t pin)
{
	uint8_t cmds[] = { FLASH_CMD_ENABLE_WRITE };

	flash_chip_select(pin);
	spi_write_blocking(spi, cmds, sizeof cmds);
	flash_chip_deselect(pin);
}

void
flash_program_page(spi_inst_t *spi, uint8_t pin, uint32_t addr, uint8_t const page[FLASH_PAGE_SIZE])
{
	uint8_t cmds[] = { FLASH_CMD_PROGRAM_PAGE, addr >> 16, addr >> 8, addr };

	assert(addr % FLASH_PAGE_SIZE == 0);

	flash_enable_write(spi, pin);
	flash_chip_select(pin);
	spi_write_blocking(spi, cmds, sizeof cmds);
	spi_write_blocking(spi, page, FLASH_PAGE_SIZE);
	flash_chip_deselect(pin);
	flash_wait(spi, pin);
}

void
flash_read(spi_inst_t *spi, uint8_t pin, uint32_t addr, uint8_t *buf, size_t sz)
{
	uint8_t cmds[] = { FLASH_CMD_READ, addr >> 16, addr >> 8, addr };

	flash_chip_select(pin);
	spi_write_blocking(spi, cmds, sizeof cmds);
	spi_read_blocking(spi, 0x00, buf, sz);
	flash_chip_deselect(pin);
}

void
flash_chip_erase(spi_inst_t *spi, uint8_t pin)
{
	uint8_t cmds[] = { FLASH_CMD_CHIP_ERASE };

	flash_chip_select(pin);
	spi_write_blocking(spi, cmds, sizeof cmds);
	flash_chip_deselect(pin);
	flash_wait(spi, pin);
}
