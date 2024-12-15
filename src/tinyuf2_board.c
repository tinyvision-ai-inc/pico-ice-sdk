// stdlib
#include <stdio.h>
#include <stdbool.h>

// pico-sdk
#include "pico/time.h"
#include "hardware/watchdog.h"
#include "hardware/timer.h"

// tinyuf2
#include "board_api.h"

// pico-ice-sdk
#include "ice_flash.h"
#include "ice_fpga.h"
#include "ice_spi.h"
#include "ice_sram.h"

static alarm_id_t alarm_id;
static bool spi_ready;
static uint32_t flash_erased[ICE_FLASH_SIZE_BYTES / (ICE_FLASH_BLOCK_SIZE * 32)];

#define SRAM_ADDR 0x20000000

void board_flash_read(uint32_t addr, void *buffer, uint32_t len)
{
    if (addr >= SRAM_ADDR) {
        addr -= SRAM_ADDR;
        ice_sram_read_blocking(addr, buffer, len);
    } else {
        ice_flash_read(addr, buffer, len);
    }
}

void board_flash_write(uint32_t addr, const void *data, uint32_t len)
{
    if (!spi_ready) {
        ice_fpga_stop();
        ice_sram_init();
        ice_flash_init();
        spi_ready = true;
    }
    if (addr >= SRAM_ADDR) {
        addr -= SRAM_ADDR;
        ice_sram_write_blocking(addr, data, len);
    } else {
        int flash_erase_idx = addr / ICE_FLASH_BLOCK_SIZE;
        if ((flash_erased[flash_erase_idx >> 5] & (1u << (flash_erase_idx & 0x1F))) == 0) {
            ice_flash_erase_block(addr & ~(ICE_FLASH_BLOCK_SIZE - 1));
            flash_erased[flash_erase_idx >> 5] |= 1u << (flash_erase_idx & 0x1F);
        }
        if (len != ICE_FLASH_PAGE_SIZE) {
            printf("%s: expected len=%u got len=%ld\r\n", __func__, ICE_FLASH_PAGE_SIZE, len);
        } else {
            ice_flash_program_page(addr, data);
        }
    }
}

void board_flash_flush(void)
{
}

uint32_t board_flash_size(void)
{
    return ICE_FLASH_SIZE_BYTES;
}

void board_rgb_write(const uint8_t rgb[])
{
    (void)rgb;
}

int64_t board_timer_handler_cb(alarm_id_t id, void *data)
{
    board_timer_handler();
    return 0;
}

void board_timer_start(uint32_t ms)
{
    alarm_id = add_alarm_in_ms(ms, board_timer_handler_cb, NULL, true);
}

void board_timer_stop(void)
{
    cancel_alarm(alarm_id);
}

void board_dfu_complete(void)
{
    watchdog_reboot(0, 0, 1000);
}
