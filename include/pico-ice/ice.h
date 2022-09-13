#include <assert.h>

/*
 * High-level API for driving the board.
 * It is under heavy development and subject to change at any time!
 */

#define ICE_FPGA_CLOCK_PIN		25
/*
 * The RP2040 pin at which a clock signal is sent, as a source for the ICE40 system clock.
 */

void ice_init_flash(void);
/*
 * Initialise the SPI1 peripheral, dedicated to flashing the FPGA.
 */

void ice_init_fpga_clock(uint8_t mhz);
/*
 * Initialise the FPGA clock at the given frequency.
 *
 * :param mhz: the clock speed in MHz. Valid values: 48MHz, 24MHz, 16MHz 12MHz, 8MHz, 6MHz, 4MHz, 3MHz, 2MHz, 1MHz.
 */
