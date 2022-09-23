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

void tud_task_cdc(void)
{
    if (uart_is_readable(uart_fpga)) {
        tud_cdc_n_write_char(1, uart_getc(uart_fpga));
        tud_cdc_n_write_flush(1);
    }
    if (tud_cdc_n_available(1)) {
        uart_putc(uart_fpga, tud_cdc_n_read_char(1));
    }
}
