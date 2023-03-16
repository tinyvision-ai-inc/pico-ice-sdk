#include <stdbool.h>
#include <stdio.h>
#include "pico/stdio.h"
#include "pico/time.h"
#include "hardware/watchdog.h"
#include "hardware/timer.h"
#include "board_api.h"
#include "ice_flash.h"
#include "ice_fpga.h"
#include "ice_led.h"
#include "ice_spi.h"

static alarm_id_t alarm_id;
static bool flash_ready;

void board_flash_read(uint32_t addr, void *buffer, uint32_t len)
{
    if (!flash_ready) {
        ice_flash_init();
        flash_ready = true;
    }

    ice_flash_read(addr, buffer, len);
}

void board_flash_write(uint32_t addr, void const *data, uint32_t len)
{
    if (!flash_ready) {
        flash_ready = true;

        // make sure the RP2040 have full access to the bus
        ice_fpga_stop();
        ice_spi_init();

        ice_flash_init();
    }

    if (len != ICE_FLASH_PAGE_SIZE) {
        printf("%s: expected len=%u got len=%ld\r\n", __func__, ICE_FLASH_PAGE_SIZE, len);
    } else {
        ice_flash_program_page(addr, data);
    }
}

void board_flash_flush(void)
{
    // synchronous read/write implementation, no need to flush
}

uint32_t board_flash_size(void)
{
    return ICE_FLASH_SIZE_BYTES;
}

void board_rgb_write(uint8_t const rgb[])
{
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
    printf("%s: rebooting\r\n", __func__);
    watchdog_reboot(0, 0, 1000);
}

void board_led_write(uint32_t rgb_pwm)
{
    uint8_t red   = rgb_pwm >> 16;
    uint8_t green = rgb_pwm >> 8;
    uint8_t blue  = rgb_pwm >> 0;

    ice_led_init();

    // Use a theshold instead of a PWM signal.
    ice_led_red(red > 0x10);
    ice_led_green(green > 0x10);
    ice_led_blue(blue > 0x10);
}
