#include "hardware/gpio.h"
#include "hardware/uart.h"
#include "hardware/watchdog.h"

#include "ice_fpga_flash.h"
#include "ice_usb.h"

// in src/tinyuf2/uf2.h
void uf2_init(void);

// in src/tinyuf2/board_api.h
void board_init(void);

/// Forward the data coming from USB CDC 1 UART to the FPGA UART.
/// Function to be called from tud_cdc_rx_cb().
void tud_cdc_rx_cb(uint8_t itf) {
    switch (itf) {
    case ICE_USB_UART_FPGA_ITF:
        while (tud_cdc_n_available(ICE_USB_UART_FPGA_ITF))
            uart_putc(uart_fpga, tud_cdc_n_read_char(ICE_USB_UART_FPGA_ITF));
        break;
    }
}

static void ice_fpga_uart_irq_handler(void) {
    while (uart_is_readable(uart_fpga)) {
        tud_cdc_n_write_char(1, uart_getc(uart_fpga));
        tud_cdc_n_write_flush(1);
    }
}

// Invoked right before tud_dfu_download_cb() (state=DFU_DNBUSY) or tud_dfu_manifest_cb() (state=DFU_MANIFEST)
// Application return timeout in milliseconds (bwPollTimeout) for the next download/manifest operation.
// During this period, USB host won't try to communicate with us.
uint32_t tud_dfu_get_timeout_cb(uint8_t alt, uint8_t state)
{
	  return 0; /* Request we are polled in 1ms */
}

// Invoked when received DFU_DNLOAD (wLength>0) following by DFU_GETSTATUS (state=DFU_DNBUSY) requests
// This callback could be returned before flashing op is complete (async).
// Once finished flashing, application must call tud_dfu_finish_flashing()
void tud_dfu_download_cb(uint8_t alt, uint16_t block_num, const uint8_t *data, uint16_t length) {
    uint32_t dest_addr = block_num * CFG_TUD_DFU_XFER_BUFSIZE;

    for (uint32_t offset = 0; offset < length; offset += ICE_FLASH_SECTOR_SIZE) {
        ice_fpga_flash_erase_sector(dest_addr + offset);
    }
    
    for (uint32_t offset = 0; offset < length; offset += ICE_FLASH_PAGE_SIZE) {
        ice_fpga_flash_program_page(dest_addr + offset, data + offset);
    }

    tud_dfu_finish_flashing(DFU_STATUS_OK);
}

// Invoked when download process is complete, received DFU_DNLOAD (wLength=0) following by DFU_GETSTATUS (state=Manifest)
// Application can do checksum, or actual flashing if buffered entire image previously.
// Once finished flashing, application must call tud_dfu_finish_flashing()
void tud_dfu_manifest_cb(uint8_t alt)
{
    tud_dfu_finish_flashing(DFU_STATUS_OK);
}

// Invoked when a DFU_DETACH request is received
void tud_dfu_detach_cb(void) {
    watchdog_reboot(0, 0, 1000);
}

static void ice_fpga_init_uart(uint32_t baudrate_hz) {
    uart_init(uart_fpga, baudrate_hz);
    gpio_set_function(ICE_FPGA_UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(ICE_FPGA_UART_RX_PIN, GPIO_FUNC_UART);

    // For forwarding UART packets to USB.
    uart_set_irq_enables(uart_fpga, true, false);
    irq_set_enabled(ICE_FPGA_UART_IRQ, true);
    irq_set_exclusive_handler(ICE_FPGA_UART_IRQ, ice_fpga_uart_irq_handler);
}

void ice_usb_init(void) {
    // TinyUSB
    board_init();
    tusb_init();

    // TinyUF2
    uf2_init();

    // Enable the UART by default, allowing early init.
    ice_fpga_init_uart(115200);
}
