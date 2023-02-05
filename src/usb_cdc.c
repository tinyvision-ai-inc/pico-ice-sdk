#include "hardware/gpio.h"
#include "hardware/uart.h"
#include "hardware/watchdog.h"

#include "ice_fpga.h"
#include "ice_fpga_bitstream.h"
#include "ice_fpga_flash.h"
#include "ice_usb.h"

/*
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
