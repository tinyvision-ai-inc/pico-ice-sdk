#include "pico/stdlib.h"
#include "pico_ice/flash.h"
#include "tusb.h"

#if 0
void tud_cdc_rx_cb(uint8_t itf)
{
    if (itf == 1 && tud_cdc_n_available(1)) {
        for (int32_t ch; (ch = tud_cdc_n_read_char(1)) >= 0;)
            uart_putc(uart_fpga, ch);
    }
}
#else
void tud_cdc_rx_cb(uint8_t itf)
{
    if (itf == 1 && tud_cdc_n_available(1)) {
        for (int32_t ch; (ch = tud_cdc_n_read_char(1)) >= 0;)
            tud_cdc_n_write_char(1, ch);
        tud_cdc_n_write_flush(1);
    }
}
#endif
