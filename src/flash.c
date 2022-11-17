#include "ice/flash.h"
#include "pico/stdlib.h"
#include "hardware/structs/spi.h"
//#include "hardware/spi.h"

#define FLASH_CMD_PROGRAM_PAGE    0x02
#define FLASH_CMD_READ            0x03
#define FLASH_CMD_ENABLE_WRITE    0x06
#define FLASH_CMD_STATUS          0x05
#define FLASH_CMD_CHIP_ERASE      0xC7

#define FLASH_STATUS_BUSY_MASK    0x01

static void spi_init(void *spi, uint64_t freq)
{
    (void)spi;
    (void)freq;
}

static uint8_t spi_xfer_byte(uint8_t tx)
{
    uint8_t rx;

    for (uint8_t i = 0; i < 8; i++) {
        // Update TX and immediately set positive edge.
        gpio_put(ICE_FLASH_SPI_TX_PIN, tx >> 7);
        gpio_put(ICE_FLASH_SPI_SCK_PIN, false);
        tx <<= 1;
        sleep_us(10);

        // Sample RX and immediately set negative edge.
        rx <<= 1;
        rx |= gpio_get(ICE_FLASH_SPI_RX_PIN);
        gpio_put(ICE_FLASH_SPI_SCK_PIN, true);
        sleep_us(10);
    }
    return rx;
}

static inline void spi_chip_select(void)
{
    gpio_put(ICE_FLASH_SPI_CSN_PIN, false);
}

static inline void spi_chip_deselect(void)
{
    gpio_put(ICE_FLASH_SPI_CSN_PIN, true);
}

static void spi_write_read_blocking(void *spi, uint8_t *buf_w, uint8_t *buf_r, size_t len)
{
    (void)spi;

    for (; len > 0; len--, buf_r++, buf_w++)
        *buf_r = spi_xfer_byte(*buf_w);
}

static void spi_read_blocking(void *spi, uint8_t tx, uint8_t *buf, size_t len)
{
    (void)spi;

    for (; len > 0; len--, buf++)
        *buf = spi_xfer_byte(tx);
}

static void spi_write_blocking(void *spi, uint8_t const *buf, size_t len)
{
    (void)spi;

    for (; len > 0; len--, buf++)
        spi_xfer_byte(*buf);
}

/**
 * Initialise the SPI1 peripheral, dedicated to flashing the FPGA.
 */
void ice_flash_init(void)
{
    // Init the SPI dedicated to flashing the FPGA
    spi_init(spi_fpga_flash, 10 * 1000 * 1000);

    // Setup the associated GPIO pins except CSN

    gpio_init(ICE_FLASH_SPI_SCK_PIN);
    gpio_put(ICE_FLASH_SPI_SCK_PIN, true);
    gpio_set_dir(ICE_FLASH_SPI_SCK_PIN, GPIO_OUT);

    gpio_init(ICE_FLASH_SPI_TX_PIN);
    gpio_put(ICE_FLASH_SPI_TX_PIN, true);
    gpio_set_dir(ICE_FLASH_SPI_TX_PIN, GPIO_OUT);

    gpio_init(ICE_FLASH_SPI_RX_PIN);
    gpio_set_dir(ICE_FLASH_SPI_RX_PIN, GPIO_IN);

    // Setup the CSN pin to GPIO mode for manual control

    gpio_init(ICE_FLASH_SPI_CSN_PIN);
    gpio_put(ICE_FLASH_SPI_CSN_PIN, true);
    gpio_set_dir(ICE_FLASH_SPI_CSN_PIN, GPIO_OUT);
}

static void ice_flash_chip_select(uint8_t pin)
{
    sleep_us(1);
    gpio_put(pin, false);
    sleep_us(1);
}

static void ice_flash_chip_deselect(uint8_t pin)
{
    sleep_us(1);
    gpio_put(pin, true);
    sleep_us(1);
}

static void ice_flash_wait(void *spi, uint8_t pin)
{
    uint8_t cmds[] = { FLASH_CMD_STATUS, 0 };
    uint8_t buf[2];

    do {
        ice_flash_chip_select(pin);
        spi_write_read_blocking(spi, cmds, buf, 2);
        ice_flash_chip_deselect(pin);
    } while (buf[0] & FLASH_STATUS_BUSY_MASK);
}

static void ice_flash_enable_write(void *spi, uint8_t pin)
{
    uint8_t cmds[] = { FLASH_CMD_ENABLE_WRITE };

    ice_flash_chip_select(pin);
    spi_write_blocking(spi, cmds, sizeof cmds);
    ice_flash_chip_deselect(pin);
}

/**
 * Program a page of the flash chip at the given address.
 * @param spi The SPI interface of the RP2040 to use.
 * @param pin The CS GPIO pin of the RP2040 to use.
 * @param addr The address at which the data is written.
 * @param page The buffer holding the data to be sent to the flash chip, of size @ref ICE_FLASH_PAGE_SIZE.
 */
void ice_flash_program_page(void *spi, uint8_t pin, uint32_t addr, uint8_t const page[ICE_FLASH_PAGE_SIZE])
{
    uint8_t cmds[] = { FLASH_CMD_PROGRAM_PAGE, addr >> 16, addr >> 8, addr };

    assert(addr % ICE_FLASH_PAGE_SIZE == 0);

    ice_flash_enable_write(spi, pin);
    ice_flash_chip_select(pin);
    spi_write_blocking(spi, cmds, sizeof cmds);
    spi_write_blocking(spi, page, ICE_FLASH_PAGE_SIZE);
    ice_flash_chip_deselect(pin);
    ice_flash_wait(spi, pin);
}

/**
 * Communicate to the chip over SPI and read multiple bytes at chosen address onto onto a buffer.
 * @param spi The SPI interface of the RP2040 to use.
 * @param pin The CS GPIO pin of the RP2040 to use.
 * @param addr The address at which the data is read.
 * @param buf The buffer onto which the data read is stored.
 * @param sz The size of ``buf``.
 */
void ice_flash_read(void *spi, uint8_t pin, uint32_t addr, uint8_t *buf, size_t sz)
{
    uint8_t cmds[] = { FLASH_CMD_READ, addr >> 16, addr >> 8, addr };

    ice_flash_chip_select(pin);
    spi_write_blocking(spi, cmds, sizeof cmds);
    spi_read_blocking(spi, 0x00, buf, sz);
    ice_flash_chip_deselect(pin);
}

/**
 * Send a command to erase the whole chip.
 * @param spi The SPI interface of the RP2040 to use.
 * @param pin The CS GPIO pin of the RP2040 to use.
 */
void ice_flash_erase_chip(void *spi, uint8_t pin)
{
    uint8_t cmds[] = { FLASH_CMD_CHIP_ERASE };

    ice_flash_chip_select(pin);
    spi_write_blocking(spi, cmds, sizeof cmds);
    ice_flash_chip_deselect(pin);
    ice_flash_wait(spi, pin);
}
