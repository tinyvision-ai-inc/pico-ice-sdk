// stdlib
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

static alarm_id_t alarm_id;
static bool flash_ready;

void board_flash_read(uint32_t addr, void *buffer, uint32_t len)
{
    if (!flash_ready) {
        ice_fpga_stop();
        ice_flash_init();
        flash_ready = true;
    }
    ice_flash_read(addr, buffer, len);
}

void board_flash_write(uint32_t addr, const void *data, uint32_t len)
{
    if (!flash_ready) {
        ice_flash_init();
        flash_ready = true;
        ice_flash_erase_chip();
    }
    if (len != ICE_FLASH_PAGE_SIZE) {
        printf("%s: expected len=%u got len=%ld\r\n", __func__, ICE_FLASH_PAGE_SIZE, len);
    } else {
        ice_flash_program_page(addr, data);
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
