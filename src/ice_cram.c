#include "hardware/gpio.h"
#include "hardware/pio.h"
#include "pico/time.h"
#include "ice_cram.h"
#include "ice_cram.pio.h"

static PIO pio;
static int sm;
static uint offset;
static const int clk_div = 30;  // 1Mbit/sec for debugging, could be much faster

static bool try_add_program(PIO try_pio) {
    if (!pio_can_add_program(try_pio, &ice_cram_program)) return false;

    sm = pio_claim_unused_sm(try_pio, false);
    if (sm < 0) return false;

    pio = try_pio;
    offset = pio_add_program(pio, &ice_cram_program);

    return true;
}

static void state_machine_init() {
    // Try to fit the program into either PIO bank
    if (!try_add_program(pio1)) {
        if (!try_add_program(pio0)) {
            panic("Could not add FPGA configuration PIO program");
        }
    }

    pio_sm_config c = ice_cram_program_get_default_config(offset);
    sm_config_set_out_pins(&c, ICE_FLASH_SPI_TX_PIN, 1);
    sm_config_set_sideset_pins(&c, ICE_FLASH_SPI_SCK_PIN);
    sm_config_set_clkdiv(&c, clk_div);
    sm_config_set_out_shift(&c, false, true, 8);
    pio_sm_init(pio, sm, offset, &c);

    pio_sm_set_enabled(pio, sm, true);

    pio_sm_set_consecutive_pindirs(pio, sm, ICE_FLASH_SPI_TX_PIN, 1, true);
    pio_sm_set_consecutive_pindirs(pio, sm, ICE_FLASH_SPI_SCK_PIN, 1, true);

    pio_gpio_init(pio, ICE_FLASH_SPI_TX_PIN);
    pio_gpio_init(pio, ICE_FLASH_SPI_SCK_PIN);
}

static void state_machine_deinit() {
    pio_sm_set_enabled(pio, sm, false);
    pio_sm_set_consecutive_pindirs(pio, sm, ICE_FLASH_SPI_TX_PIN, 1, false);
    pio_sm_set_consecutive_pindirs(pio, sm, ICE_FLASH_SPI_SCK_PIN, 1, false);
    pio_remove_program(pio, &ice_cram_program, offset);
    pio_sm_unclaim(pio, sm);
}

static void put_byte(uint8_t data) {
    // FIFO slots are 32-bits and the PIO state machine left shifts to get MSB first so need to
    // pre-shift by 24 bits to get bit 7 of data byte into bit 31 of FIFO slot.
    pio_sm_put_blocking(pio, sm, data << 24);
}

static void wait_idle() {
    // Wait until the last byte has been pulled from the FIFO.
    while (!pio_sm_is_tx_fifo_empty(pio, sm)) {
        tight_loop_contents();
    }

    // At this point the last byte has been removed from the FIFO but the last bit might not have
    // been shifted out. Wait for the state machine to stall waiting for another bit
    // (which night never arrive).
    uint32_t mask = 1u << (sm + PIO_FDEBUG_TXSTALL_LSB);
    pio->fdebug = mask;
    while ((pio->fdebug & mask) == 0) {
        tight_loop_contents();
    }
}

void ice_cram_open(void) {
    // Hold FPGA in reset before doing anything with SPI bus.
    gpio_put(ICE_FPGA_CRESET_PIN, false);

    state_machine_init();

    // SPI_SS low signals FPGA to receive bitstream.
    gpio_init(ICE_FLASH_SPI_CSN_PIN);
    gpio_put(ICE_FLASH_SPI_CSN_PIN, false);
    gpio_set_dir(ICE_FLASH_SPI_CSN_PIN, GPIO_OUT);

    // Bring FPGA out of reset after at least 200ns.
    busy_wait_us(2);
    gpio_put(ICE_FPGA_CRESET_PIN, true);

    // At least 1200us for FPGA to clear internal configuration memory.
    busy_wait_us(1300);

    // SPI_SS high for 8 SPI_SCLKs
    gpio_put(ICE_FLASH_SPI_CSN_PIN, true);
    put_byte(0);
    wait_idle();
    gpio_put(ICE_FLASH_SPI_CSN_PIN, false);
}

bool ice_cram_write(const uint8_t* bitstream, uint32_t size) {
    for (uint32_t i = 0; i < size; ++i) {
        put_byte(bitstream[i]);
    }
}

bool ice_cram_close(void) {
    wait_idle();

    // Bring SPI_SS high at end of bitstream and leave it pulled up.
    gpio_put(ICE_FLASH_SPI_CSN_PIN, true);
    sleep_us(1);
    gpio_pull_up(ICE_FLASH_SPI_CSN_PIN);
    gpio_set_dir(ICE_FLASH_SPI_CSN_PIN, GPIO_IN);

    // Output dummy bytes. CDONE should go high within 100 SCLKs or there was an error with the bitstream.
    for (int i = 0; i < 13; ++i) {
        put_byte(0);
        if (gpio_get(ICE_FPGA_CDONE_PIN)) break;
    }

    // At least another 49 SCLK cycles once CDONE goes high.
    for (int i = 0; i < 7; ++i) {
        put_byte(0);
    }

    wait_idle();
    state_machine_deinit();

    return gpio_get(ICE_FPGA_CDONE_PIN);
}
