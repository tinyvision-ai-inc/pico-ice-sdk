#include <stdio.h>
#include "ice/flash.h"
#include "hardware/watchdog.h"
#include "hardware/timer.h"
#include "board_api.h"

alarm_id_t alarm_id;

void
board_flash_read(uint32_t addr, void *buffer, uint32_t len)
{
    ice_flash_read(spi_fpga_flash, ICE_FLASH_SPI_CSN_PIN, addr, buffer, len);
}

void
board_flash_write(uint32_t addr, void const *data, uint32_t len)
{
    if (len != ICE_FLASH_PAGE_SIZE) {
        printf("%s: expected len=%u got len=%ld\r\n", __func__, ICE_FLASH_PAGE_SIZE, len);
    } else {
        ice_flash_program_page(spi_fpga_flash, ICE_FLASH_SPI_CSN_PIN, addr, data);
    }
}

void
board_flash_flush(void)
{
    // synchronous read/write implementation, no need to flush
}

uint32_t
board_flash_size(void)
{
    return ICE_FPGA_FLASH_SIZE_BYTES;
}

void
board_rgb_write(uint8_t const rgb[])
{
}

int64_t
board_timer_handler_cb(alarm_id_t id, void *data)
{
    board_timer_handler();
    return 0;
}

void
board_timer_start(uint32_t ms)
{
    alarm_id = add_alarm_in_ms(ms, board_timer_handler_cb, NULL, true);
}

void
board_timer_stop(void)
{
    cancel_alarm(alarm_id);
}

void
board_dfu_complete(void)
{
    printf("%s: rebooting\r\n", __func__);
    watchdog_reboot(0, 0, 1000);
}
