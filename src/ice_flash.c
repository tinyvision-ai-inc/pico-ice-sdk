#include "pico/stdio.h"
#include "pico/stdlib.h"
#include "hardware/structs/spi.h"

#include "ice_flash.h"
#include "ice_fpga.h"

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

static uint8_t soft_spi_delay(void) {
    for (volatile uint8_t i = 0; i < 0x4; i++); // Leads to approx 1MHz SPI clock
}

static uint8_t soft_spi_xfer_byte(uint8_t tx) {
    uint8_t rx;

    for (uint8_t i = 0; i < 8; i++) {
        // Update TX and immediately set negative edge.
        gpio_put(ICE_FLASH_SPI_SCK_PIN, false);
        gpio_put(ICE_FLASH_SPI_TX_PIN, tx >> 7);
        tx <<= 1;

        // stable for a while with clock low
        soft_spi_delay();

        // Sample RX as we set positive edge.
        rx <<= 1;
        rx |= gpio_get(ICE_FLASH_SPI_RX_PIN);
        gpio_put(ICE_FLASH_SPI_SCK_PIN, true);

        // stable for a while with clock high
        soft_spi_delay();
    }
    return rx;
}

static void soft_spi_chip_select(void) {
    gpio_put(ICE_FLASH_SPI_SCK_PIN, false);
    soft_spi_delay();
    gpio_put(ICE_FLASH_SPI_CSN_PIN, false);
    soft_spi_delay();
}

static void soft_spi_chip_deselect(void) {
    gpio_put(ICE_FLASH_SPI_SCK_PIN, false);
    soft_spi_delay();
    gpio_put(ICE_FLASH_SPI_CSN_PIN, true);
    soft_spi_delay();
}

static void soft_spi_write_read_blocking(uint8_t *buf_w, uint8_t *buf_r, size_t len) {
    for (; len > 0; len--, buf_r++, buf_w++)
        *buf_r = soft_spi_xfer_byte(*buf_w);
}

static void soft_spi_read_blocking(uint8_t tx, uint8_t *buf, size_t len) {
    for (; len > 0; len--, buf++)
        *buf = soft_spi_xfer_byte(tx);
}

static void soft_spi_write_blocking(uint8_t const *buf, size_t len) {
    for (; len > 0; len--, buf++)
        soft_spi_xfer_byte(*buf);
}

void ice_flash_enable_write(void) {
    uint8_t cmds[] = { FLASH_CMD_ENABLE_WRITE };

    soft_spi_chip_select();
    soft_spi_write_blocking(cmds, sizeof cmds);
    soft_spi_chip_deselect();
}

void ice_flash_init(void) {
    // Hold the FPGA in reset while flashing so that it does not interfer.
    ice_halt();

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
    ice_flash_wakeup();
}

void ice_flash_deinit(void) {
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

static void ice_flash_wait(void) {
    uint8_t cmds[] = { FLASH_CMD_STATUS, 0 };
    uint8_t buf[2];

    do {
        soft_spi_chip_select();
        soft_spi_write_read_blocking(cmds, buf, 2);
        soft_spi_chip_deselect();

    } while (buf[1] & FLASH_STATUS_BUSY_MASK);
}

void ice_flash_erase_sector(uint32_t addr) {
    uint8_t cmds[] = { FLASH_CMD_SECTOR_ERASE, addr >> 16, addr >> 8, addr };

    assert(addr % ICE_FLASH_SECTOR_SIZE == 0);

    ice_flash_enable_write();

    soft_spi_chip_select();
    soft_spi_write_blocking(cmds, sizeof cmds);
    soft_spi_chip_deselect();

    ice_flash_wait();
}

void ice_flash_program_page(uint32_t addr, uint8_t const page[ICE_FLASH_PAGE_SIZE]) {
    uint8_t cmds[] = { FLASH_CMD_PROGRAM_PAGE, addr >> 16, addr >> 8, addr };

    assert(addr % ICE_FLASH_PAGE_SIZE == 0);

    ice_flash_enable_write();

    soft_spi_chip_select();
    soft_spi_write_blocking(cmds, sizeof cmds);
    soft_spi_write_blocking(page, ICE_FLASH_PAGE_SIZE);
    soft_spi_chip_deselect();

    ice_flash_wait();
}

void ice_flash_read(uint32_t addr, uint8_t *buf, size_t sz) {
    uint8_t cmds[] = { FLASH_CMD_READ, addr >> 16, addr >> 8, addr };

    soft_spi_chip_select();
    soft_spi_write_blocking(cmds, sizeof cmds);
    soft_spi_read_blocking(0x00, buf, sz);
    soft_spi_chip_deselect();
}

void ice_flash_erase_chip(void) {
    uint8_t cmds[] = { FLASH_CMD_CHIP_ERASE };

    ice_flash_enable_write();

    soft_spi_chip_select();
    soft_spi_write_blocking(cmds, sizeof cmds);
    soft_spi_chip_deselect();

    ice_flash_wait();
}

void ice_flash_wakeup(void) {
    uint8_t cmds[] = { FLASH_CMD_RELEASE_POWERDOWN };

    soft_spi_chip_select();
    soft_spi_write_blocking(cmds, sizeof cmds);
    soft_spi_chip_deselect();

    ice_flash_wait();
}

void ice_flash_sleep(void) {
    uint8_t cmds[] = { FLASH_CMD_POWERDOWN };

    soft_spi_chip_select();
    soft_spi_write_blocking(cmds, sizeof cmds);
    soft_spi_chip_deselect();

    ice_flash_wait();
}
