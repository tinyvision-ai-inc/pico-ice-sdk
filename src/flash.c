#include <stdlib.h>
#include <stdio.h>
#include "ice/flash.h"
#include "ice/fpga.h"
#include "pico/stdlib.h"
#include "hardware/structs/spi.h"

#define FLASH_CMD_PROGRAM_PAGE       0x02
#define FLASH_CMD_READ               0x03
#define FLASH_CMD_ENABLE_WRITE       0x06
#define FLASH_CMD_STATUS             0x05
#define FLASH_CMD_SECTOR_ERASE       0x20
#define FLASH_CMD_CHIP_ERASE         0xC7
#define FLASH_CMD_RELEASE_POWERDOWN  0xAB
#define FLASH_CMD_POWERDOWN          0xB9

#define FLASH_STATUS_BUSY_MASK       0x01

#define LOG(fmt, ...) printf("%s: " fmt "\r\n", __func__, ##__VA_ARGS__)

static void soft_spi_init(void *spi, uint64_t freq) {
    (void)spi;
    (void)freq;
}

static uint8_t soft_spi_delay(void)
{
    for (volatile uint8_t i = 0; i < 0xF; i++);
}

static uint8_t soft_spi_xfer_byte(uint8_t tx) {
    uint8_t rx;

    for (uint8_t i = 0; i < 8; i++) {
        // Update TX and immediately set positive edge.
        gpio_put(ICE_FLASH_SPI_TX_PIN, tx >> 7);
        soft_spi_delay();
        gpio_put(ICE_FLASH_SPI_SCK_PIN, true);
        tx <<= 1;
        soft_spi_delay();

        // Sample RX and immediately set negative edge.
        rx <<= 1;
        rx |= gpio_get(ICE_FLASH_SPI_RX_PIN);
        soft_spi_delay();
        gpio_put(ICE_FLASH_SPI_SCK_PIN, false);
        soft_spi_delay();
    }
    return rx;
}

static void soft_spi_chip_select(uint8_t pin) {
    gpio_put(pin, false);
    sleep_us(10);
}

static void soft_spi_chip_deselect(uint8_t pin) {
    gpio_put(pin, true);
    sleep_us(10);
}

static void soft_spi_write_read_blocking(void *spi, uint8_t *buf_w, uint8_t *buf_r, size_t len) {
    (void)spi;

    for (; len > 0; len--, buf_r++, buf_w++)
        *buf_r = soft_spi_xfer_byte(*buf_w);
}

static void soft_spi_read_blocking(void *spi, uint8_t tx, uint8_t *buf, size_t len) {
    (void)spi;

    for (; len > 0; len--, buf++)
        *buf = soft_spi_xfer_byte(tx);
}

static void soft_spi_write_blocking(void *spi, uint8_t const *buf, size_t len) {
    (void)spi;

    for (; len > 0; len--, buf++)
        soft_spi_xfer_byte(*buf);
}

static void ice_flash_enable_write(void *spi, uint8_t pin) {
    uint8_t cmds[] = { FLASH_CMD_ENABLE_WRITE };

    soft_spi_chip_select(pin);
    soft_spi_write_blocking(spi, cmds, sizeof cmds);
    soft_spi_chip_deselect(pin);
}

/// Initialise the SPI1 peripheral, dedicated to flashing the FPGA.
void ice_flash_init(void) {
    // Hold the FPGA in reset while flashing so that it does not interfer.
    ice_fpga_halt();

    // Init the SPI dedicated to flashing the FPGA
    soft_spi_init(spi_fpga_flash, 10 * 1000 * 1000);

    // Setup the associated GPIO pins except CSN

    gpio_init(ICE_FLASH_SPI_SCK_PIN);
    gpio_put(ICE_FLASH_SPI_SCK_PIN, false); // SCK should start low
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

    // Flash might be asleep as a successful FPGA boot will put it to sleep as the last command!
    ice_flash_wakeup(spi_fpga_flash, ICE_FLASH_SPI_CSN_PIN);

    // Enable writing to the flash once here for all subsequent invocations.
    ice_flash_enable_write(spi_fpga_flash, ICE_FLASH_SPI_CSN_PIN);
}

/// Release the GPIO used for the FPGA flash so the FPGA can use them
void ice_flash_deinit(void) {
    // Init the SPI dedicated to flashing the FPGA
    soft_spi_init(spi_fpga_flash, 10 * 1000 * 1000);

    // Setup the associated GPIO pins except CSN

    gpio_init(ICE_FLASH_SPI_SCK_PIN);
    gpio_set_dir(ICE_FLASH_SPI_SCK_PIN, GPIO_IN);

    gpio_init(ICE_FLASH_SPI_TX_PIN);
    gpio_set_dir(ICE_FLASH_SPI_TX_PIN, GPIO_IN);

    gpio_init(ICE_FLASH_SPI_RX_PIN);
    gpio_set_dir(ICE_FLASH_SPI_RX_PIN, GPIO_IN);

    gpio_init(ICE_FLASH_SPI_CSN_PIN);
    gpio_set_dir(ICE_FLASH_SPI_CSN_PIN, GPIO_IN);
}

static void ice_flash_wait(void *spi, uint8_t pin) {
    uint8_t cmds[] = { FLASH_CMD_STATUS, 0 };
    uint8_t buf[2];

    do {
        soft_spi_chip_select(pin);
        soft_spi_write_read_blocking(spi, cmds, buf, 2);
        soft_spi_chip_deselect(pin);
    } while (buf[1] & FLASH_STATUS_BUSY_MASK);
}

/// Erase a sector of the flash chip at the given address.
/// \param spi The SPI interface of the RP2040 to use.
/// \param pin The CS GPIO pin of the RP2040 to use.
/// \param addr The beginning of the sector
void ice_flash_erase_sector(void *spi, uint8_t pin, uint32_t addr) {
    uint8_t cmds[] = { FLASH_CMD_SECTOR_ERASE, addr >> 16, addr >> 8, addr };

    assert(addr % ICE_FLASH_PAGE_SIZE == 0);

    soft_spi_chip_select(pin);
    soft_spi_write_blocking(spi, cmds, sizeof cmds);
    soft_spi_chip_deselect(pin);

    ice_flash_wait(spi, pin);
}

/// Program a page of the flash chip at the given address.
/// \param spi The SPI interface of the RP2040 to use.
/// \param pin The CS GPIO pin of the RP2040 to use.
/// \param addr The address at which the data is written.
/// \param page The buffer holding the data to be sent to the flash chip, of size @ref ICE_FLASH_PAGE_SIZE.
void ice_flash_program_page(void *spi, uint8_t pin, uint32_t addr, uint8_t const page[ICE_FLASH_PAGE_SIZE])
{
    uint8_t cmds[] = { FLASH_CMD_PROGRAM_PAGE, addr >> 16, addr >> 8, addr };

    assert(addr % ICE_FLASH_PAGE_SIZE == 0);
    ice_flash_enable_write(spi, pin);

    soft_spi_chip_select(pin);
    soft_spi_write_blocking(spi, cmds, sizeof cmds);
    soft_spi_write_blocking(spi, page, ICE_FLASH_PAGE_SIZE);
    soft_spi_chip_deselect(pin);

    ice_flash_wait(spi, pin);
}

/// Communicate to the chip over SPI and read multiple bytes at chosen address onto onto a buffer.
/// \param spi The SPI interface of the RP2040 to use.
/// \param pin The CS GPIO pin of the RP2040 to use.
/// \param addr The address at which the data is read.
/// \param buf The buffer onto which the data read is stored.
/// \param sz The size of ``buf``.
void ice_flash_read(void *spi, uint8_t pin, uint32_t addr, uint8_t *buf, size_t sz)
{
    uint8_t cmds[] = { FLASH_CMD_READ, addr >> 16, addr >> 8, addr };

    soft_spi_chip_select(pin);
    soft_spi_write_blocking(spi, cmds, sizeof cmds);
    soft_spi_read_blocking(spi, 0x00, buf, sz);
    soft_spi_chip_deselect(pin);
}

/// Send a command to erase the whole chip.
/// \param spi The SPI interface of the RP2040 to use.
/// \param pin The CS GPIO pin of the RP2040 to use.
void ice_flash_erase_chip(void *spi, uint8_t pin)
{
    uint8_t cmds[] = { FLASH_CMD_CHIP_ERASE };

    soft_spi_chip_select(pin);
    soft_spi_write_blocking(spi, cmds, sizeof cmds);
    soft_spi_chip_deselect(pin);

    ice_flash_wait(spi, pin);
}

/// Send a command to wakeup the chip.
/// \param spi The SPI interface of the RP2040 to use.
/// \param pin The CS GPIO pin of the RP2040 to use.
void ice_flash_wakeup(void *spi, uint8_t pin)
{
    uint8_t cmds[] = { FLASH_CMD_RELEASE_POWERDOWN };

    soft_spi_chip_select(pin);
    soft_spi_write_blocking(spi, cmds, sizeof cmds);
    soft_spi_chip_deselect(pin);

    ice_flash_wait(spi, pin);
}

/// Send a command to put the chip to sleep.
/// \param spi The SPI interface of the RP2040 to use.
/// \param pin The CS GPIO pin of the RP2040 to use.
void ice_flash_sleep(void *spi, uint8_t pin) {
    uint8_t cmds[] = { FLASH_CMD_POWERDOWN };

    soft_spi_chip_select(pin);
    soft_spi_write_blocking(spi, cmds, sizeof cmds);
    soft_spi_chip_deselect(pin);

    ice_flash_wait(spi, pin);
}
