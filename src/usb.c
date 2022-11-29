#include "ice/usb.h"
#include "hardware/uart.h"

/**
 * Forward the data coming from USB CDC 1 UART to the FPGA UART.
 * Function to be called from tud_cdc_rx_cb().
 */
void tud_cdc_rx_cb(uint8_t itf)
{
    switch (itf) {
    case ICE_USB_UART_FPGA_ITF:
        while (tud_cdc_n_available(ICE_USB_UART_FPGA_ITF))
            uart_putc(uart_fpga, tud_cdc_n_read_char(ICE_USB_UART_FPGA_ITF));
        break;
    }
}

/**
 * Initialise the TinyUSB library, enabling the UART (CDC) and drag-and-drop (MSC) interfaces.
 */
void ice_usb_init(void)
{
    // TinyUSB
    board_init();
    tusb_init();

    // TinyUF2
    uf2_init();
}

/**
 * Run all code related to USB in a non-blocking way.
 * It is typically to be placed at the end of the main application loop.
 */
void ice_usb_task(void)
{
    tud_task();
}
