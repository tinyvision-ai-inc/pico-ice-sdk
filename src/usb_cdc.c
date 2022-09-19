#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "pico/stdlib.h"
#include "pico/stdio.h"
#include "hardware/gpio.h"
#include "pico_ice/flash.h"
#include "pico_ice/ice.h"
#include "tusb.h"

void
tud_task_cdc(void)
{
    static char buf[64] = {0};
    static size_t pos = 0, sz = 0;

    if (uart_is_readable(uart_fpga))
        uart_putc(uart_fpga, toupper(uart_getc(uart_fpga)));

    if (tud_cdc_n_available(ITF_NUM_CDC_PICO)) {
        uart_putc(uart_fpga, 'p');
        tud_cdc_n_write_char(ITF_NUM_CDC_PICO, 'p');
        tud_cdc_n_write_flush(ITF_NUM_CDC_PICO);
    }

    if (tud_cdc_n_available(ITF_NUM_CDC_FPGA)) {
        uart_putc(uart_fpga, 'f');
        tud_cdc_n_write_char(ITF_NUM_CDC_FPGA, 'f');
        tud_cdc_n_write_flush(ITF_NUM_CDC_FPGA);
    }

    return;

    // limit to 64 bytes in a row to make sure not to block the app
    for (int n = 64; n > 0 && uart_is_readable(uart_fpga); n--) {
        printf("[%c]", uart_getc(uart_fpga));
        tud_cdc_n_write_char(ITF_NUM_CDC_FPGA, uart_getc(uart_fpga));
    }
    tud_cdc_n_write_flush(ITF_NUM_CDC_FPGA);

    // not looping to avoid blocking the app, will continue at next iteration
    if (pos == sz) {
        sz = tud_cdc_n_read(ITF_NUM_CDC_FPGA, buf, sizeof(buf));
        pos = 0;
    }
    for (; pos < sz && uart_is_writable(uart_fpga); pos++) {
        printf("[%c]", buf[pos]);
        uart_putc(uart_fpga, buf[pos]);
    }
}
