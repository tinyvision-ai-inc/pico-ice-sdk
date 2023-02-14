#include "hardware/irq.h"
#include "ice_usb.h"

int main(void) {
    // Stdio bound to USB CDC0 by default
    stdio_init_all();

    // Enable the UART by default, allowing early init.
    uart_init(uart_fpga, 115200);
    gpio_set_function(0, GPIO_FUNC_UART);
    gpio_set_function(1, GPIO_FUNC_UART);

    // Bind USB CDC1 callback for piping to UART0
    tud_cdc_rx_cb_table[1] = ice_usb_cdc_to_uart0;

    // Bind UART0 interrupt for piping to USB CDC1
    irq_set_exclusive_handler(UART0_IRQ, ice_usb_uart0_to_cdc1):

    for (;;) {
        tud_task();

        // Extra code here
    }
    return 0;
}
