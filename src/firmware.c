#include "pico/stdlib.h"
#include "pico/stdio.h"
<<<<<<< HEAD
#include "hardware/gpio.h"
#include "pico-ice/flash.h"
#include "pico-ice/ice.h"
#include "tusb.h"
#include "hardware/pll.h"
#include "hardware/clocks.h"
#include "hardware/structs/pll.h"
#include "hardware/structs/clocks.h"
#include "time.h"

#define ICE_SO      0
#define ICE_SSn     1
#define ICE_SCK     2
#define ICE_SI      3
#define ICE_DONE    26
#define ICE_RSTn    27

#define RED_LED     24
#define GREEN_LED   23
#define BLUE_LED    22

#define GPIO_HI     1
#define GPIO_LO     0
#define LED_ON      false
#define LED_OFF     true

static void
cdc_task(void)
{
    uint8_t buf[64];
    uint32_t sz;

    if (!tud_cdc_n_available(0))
        return;

    sz = tud_cdc_n_read(0, buf, sizeof(buf));
    for (uint32_t i = 0; i < sz; i++)
        tud_cdc_n_write_char(0, toupper(buf[i]));
    tud_cdc_n_write_flush(0);
}
=======
#include "pico_ice/ice.h"
>>>>>>> 56e77b441935e620236e9cca6043f28d3f508b5c

static void send_buf(uint8_t *buf) {
    for (uint8_t i = 0; i<strlen(buf); i++)
        tud_cdc_n_write_char(0, *(buf + i) );
    tud_cdc_n_write_flush(0);
}

static void setup_pico_ice (void) {
    gpio_init(RED_LED);
    gpio_init(GREEN_LED);
    gpio_init(BLUE_LED);
    gpio_set_dir_out_masked( (1 << RED_LED) | (1<<GREEN_LED) | (1<<BLUE_LED) );
    tusb_init();
 
    // Safe FGA settings:
    gpio_init(ICE_RSTn);
    gpio_init(ICE_DONE);
    gpio_init(ICE_SSn);
    gpio_init(ICE_SI);
    gpio_pull_up(ICE_RSTn);
    gpio_pull_up(ICE_DONE);
    gpio_pull_up(ICE_SSn);
    gpio_pull_up(ICE_SI);
 
    gpio_set_dir_in_masked( (1<<ICE_DONE) | (1<<ICE_SSn) | (1<<ICE_SO)
                          | (1<<ICE_SI)   | (1<<ICE_SCK) | (1<<ICE_RSTn));
}
 
static void reset_fpga(void) {
        // Reset the FPGA:
    gpio_set_dir_out_masked( (1 << ICE_RSTn) );
    gpio_put(ICE_RSTn, GPIO_LO);
    sleep_ms(10); // Reset time
    // Let the ICE boot up
    gpio_put(ICE_RSTn, GPIO_HI);
    gpio_set_dir_in_masked( (1 << ICE_RSTn) );

}

// How long should the LED be ON?
#define LED_FREQ 200

int main(void)
{
    stdio_init_all();

    ice_flash_init();

    setup_pico_ice();

    reset_fpga();
    
    clock_gpio_init(21, CLOCKS_CLK_GPOUT0_CTRL_AUXSRC_VALUE_CLK_USB, 4);
    clock_gpio_init(25, CLOCKS_CLK_GPOUT0_CTRL_AUXSRC_VALUE_CLK_USB, 8);

    for (;;) {
        gpio_put(BLUE_LED, LED_OFF);
        gpio_put(RED_LED, LED_ON);
        sleep_ms(200);
        gpio_put(RED_LED, LED_OFF);
        gpio_put(GREEN_LED, LED_ON);
        sleep_ms(200);
        gpio_put(GREEN_LED, LED_OFF);
        gpio_put(BLUE_LED, LED_ON);
        sleep_ms(200);
        tud_task();
        cdc_task();
        send_buf(".");
    }

    return 0;
}
