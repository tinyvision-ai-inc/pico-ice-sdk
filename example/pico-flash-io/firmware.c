#include "pico/stdlib.h"
#include "pico/stdio.h"

#include "boards/pico_ice.h"

#include "ice_sdk.h"
#include "ice_usb.h"
#include "ice_fpga_flash.h"
#include "ice_fpga.h"

#define MY_BASE_ADDRESS 0x00000

static inline void memdump(uint8_t const *buf, size_t sz) {
    for (size_t i = 0; i < sz; i++) {
        printf(" %02X", buf[i]);
        if (i % 0x40 == (0x40 - 1))
            printf("\r\n");
    }
    printf("\r\n");
}

int main(void) {
    uint8_t buf_r[ICE_FLASH_PAGE_SIZE] = {0}, buf_w[ICE_FLASH_PAGE_SIZE] = {0};

    // Let the FPGA boot up from flash
    ice_sdk_init();

    // Enable USB-UART #0 output
    stdio_init_all();

    // Booted up, now take control of the Flash
    ice_fpga_flash_init();

    // Write data: known pattern, not very random!
    for (size_t i = 0; i < sizeof buf_w; i++) {
        buf_w[i] = i;
    }

    for (uint16_t i = 0;; i++) {
        tud_task(); 

        // Erase a sector, program the page and then read it back.
        // Note that we're using MY_BASE_ADDRESS to avoid erasing the FPGA bitfile which is at 0x0
        ice_fpga_flash_erase_sector(MY_BASE_ADDRESS);
        ice_fpga_flash_program_page(MY_BASE_ADDRESS, buf_w);
        ice_fpga_flash_read(MY_BASE_ADDRESS, buf_r, sizeof buf_r);
        memdump(buf_r, sizeof buf_r);
    }

    return 0;
}
