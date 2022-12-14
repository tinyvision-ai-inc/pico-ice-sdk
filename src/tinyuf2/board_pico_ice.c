#include <stdbool.h>
#include <stdio.h>

#include "pico/stdio.h"
#include "pico/time.h"
#include "hardware/watchdog.h"
#include "hardware/timer.h"
#include "board_api.h"

#include "ice_fpga_flash.h"

alarm_id_t alarm_id;
bool flash_ready = false;

void board_flash_init(void) {
    if (!flash_ready) {
        ice_fpga_flash_init();
        flash_ready = true;
    }
}

void board_flash_read(uint32_t addr, void *buffer, uint32_t len) {
    board_flash_init();
    ice_fpga_flash_read(addr, buffer, len);
}

void board_flash_write(uint32_t addr, void const *data, uint32_t len) {
    board_flash_init();
    if (len != ICE_FLASH_PAGE_SIZE) {
        printf("%s: expected len=%u got len=%ld\r\n", __func__, ICE_FLASH_PAGE_SIZE, len);
    } else {
        ice_fpga_flash_program_page(addr, data);
    }
}

void board_flash_flush(void) {
    // synchronous read/write implementation, no need to flush
}

uint32_t board_flash_size(void) {
    return ICE_FPGA_FLASH_SIZE_BYTES;
}

void board_rgb_write(uint8_t const rgb[]) {
}

int64_t board_timer_handler_cb(alarm_id_t id, void *data) {
    board_timer_handler();
    return 0;
}

void board_timer_start(uint32_t ms) {
    alarm_id = add_alarm_in_ms(ms, board_timer_handler_cb, NULL, true);
}

void board_timer_stop(void) {
    cancel_alarm(alarm_id);
}

void board_dfu_complete(void) {
    printf("%s: rebooting\r\n", __func__);
    watchdog_reboot(0, 0, 1000);
}
