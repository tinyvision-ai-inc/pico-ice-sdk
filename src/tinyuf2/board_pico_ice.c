#include <stdio.h>
#include "pico_ice/flash.h"
#include "board_api.h"

void
board_flash_read(uint32_t addr, void *buffer, uint32_t len)
{
    (void)addr;

    printf("0");
    flash_read(spi_fpga_flash, ICE_FLASH_SPI_CSN_PIN, addr, buffer, len);
}

void
board_flash_write(uint32_t addr, void const *data, uint32_t len)
{
    printf("1");
    if (len == FLASH_PAGE_SIZE)
        flash_program_page(spi_fpga_flash, ICE_FLASH_SPI_CSN_PIN, addr, data);
    for (size_t i = 0; i < len; i++) {
        if (i % 32 == 0)
            printf("\n 0x%08lX  ", addr + i);
        printf(" %02zX", ((char *)data)[i]);
    }
    printf("\n");
}

void
board_flash_flush(void)
{
    printf("7");
}

uint32_t
board_flash_size(void)
{
    printf("2");
    return 1024;
}

void
board_rgb_write(uint8_t const rgb[])
{
    printf("3");
}

void
board_timer_start(uint32_t ms)
{
    (void)ms;
    printf("4");
}

void
board_timer_stop(void)
{
    printf("5");
}

void
board_dfu_complete(void)
{
    printf("6");
}
