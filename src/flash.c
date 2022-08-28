#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "pico-ice/flash.h"

#define FLASH_CMD_PROGRAM_PAGE	0x02
#define FLASH_CMD_READ		0x03
#define FLASH_CMD_ENABLE_WRITE	0x06
#define FLASH_CMD_STATUS	0x05

#define FLASH_STATUS_BUSY_MASK	0x01

static void
cs_select(void)
{
	sleep_us(1);
	gpio_put(PICO_DEFAULT_SPI_CSN_PIN, false);
	sleep_us(1);
}

static void
cs_deselect(void)
{
	sleep_us(1);
	gpio_put(PICO_DEFAULT_SPI_CSN_PIN, true);
	sleep_us(1);
}

static void
flash_wait(spi_inst_t *spi)
{
	uint8_t cmds[] = { FLASH_CMD_STATUS, 0 };
	uint8_t buf[2];

	do {
		cs_select();
		spi_write_read_blocking(spi, cmds, buf, 2);
		cs_deselect();
	} while (buf[0] & FLASH_STATUS_BUSY_MASK);
}

static void
flash_enable_write(spi_inst_t *spi)
{
	uint8_t cmds[] = { FLASH_CMD_ENABLE_WRITE };

	cs_select();
	spi_write_blocking(spi, cmds, sizeof cmds);
	cs_deselect();
}

void
flash_program_page(spi_inst_t *spi, uint32_t addr, uint8_t const page[FLASH_PAGE_SIZE])
{
	uint8_t cmds[] = { FLASH_CMD_PROGRAM_PAGE, addr >> 16, addr >> 8, addr };

	assert(addr % FLASH_PAGE_SIZE == 0);

	flash_enable_write(spi);
	cs_select();
	spi_write_blocking(spi, cmds, sizeof cmds);
	spi_write_blocking(spi, page, FLASH_PAGE_SIZE);
	cs_deselect();
	flash_wait(spi);
}

void
flash_read_page(spi_inst_t *spi, uint32_t addr, uint8_t page[FLASH_PAGE_SIZE])
{
	flash_read(spi, addr, page, FLASH_PAGE_SIZE);
}

void
flash_read(spi_inst_t *spi, uint32_t addr, uint8_t *buf, size_t sz)
{
	uint8_t cmds[] = { FLASH_CMD_READ, addr >> 16, addr >> 8, addr };

	cs_select();
	spi_write_blocking(spi, cmds, sizeof cmds);
	spi_read_blocking(spi, 0x00, buf, sz);
	cs_deselect();
}

void
flash_sector_erase(spi_inst_t *spi_default, uint8_t addr)
{

}
