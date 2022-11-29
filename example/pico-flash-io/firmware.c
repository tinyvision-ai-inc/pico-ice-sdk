#include "pico/stdlib.h"
#include "pico/stdio.h"
#include "ice/init.h"
#include "ice/usb.h"
#include "ice/flash.h"
#include "ice/fpga.h"
#include "boards/pico_ice.h"

static inline void memdump(uint8_t const *buf, size_t sz)
{
    printf("up=%d ", gpio_is_pulled_up(ICE_FLASH_SPI_RX_PIN));
    printf("dn=%d ", gpio_is_pulled_down(ICE_FLASH_SPI_RX_PIN));
    printf("hy=%d ", gpio_is_input_hysteresis_enabled(ICE_FLASH_SPI_RX_PIN));
    for (size_t i = 0; i < sz; i++) {
        printf(" %02X", buf[i]);
        if (i % 0x40 == (0x40 - 1))
            printf("\r\n");
    }
    printf("\r\n");
}

int
main(void)
{
    uint8_t buf_r[ICE_FLASH_PAGE_SIZE] = {0}, buf_w[ICE_FLASH_PAGE_SIZE] = {0};

    ice_init();
    gpio_set_input_hysteresis_enabled(ICE_FLASH_SPI_RX_PIN, false);

    for (size_t i = 0; i < sizeof buf_w; i++)
        buf_w[i] = 3;

    for (uint16_t i = 0;; i++) {
        ice_usb_task(); 

        //ice_flash_program_page(spi_fpga_flash, ICE_FLASH_SPI_CSN_PIN, 0x0000, buf_w);
        ice_flash_read(spi_fpga_flash, ICE_FLASH_SPI_CSN_PIN, i, buf_r, sizeof buf_r);
        memdump(buf_r, sizeof buf_r);
    }

    return 0;
}
