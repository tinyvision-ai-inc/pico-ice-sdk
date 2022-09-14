#include "board_api.h"

void
board_flash_read(uint32_t addr, void* buffer, uint32_t len)
{
    (void)addr;
    (void)buffer;
    (void)len;
}

void
board_flash_write(uint32_t addr, void const *data, uint32_t len)
{
    (void)addr;
    (void)data;
    (void)len;
}

void
board_flash_flush(void)
{
}

uint32_t
board_flash_size(void)
{
}

void
board_rgb_write(uint8_t const rgb[])
{
}

void
board_timer_start(uint32_t ms)
{
	(void)ms;
}

void
board_timer_stop(void)
{
}

void
board_dfu_complete(void)
{
}
