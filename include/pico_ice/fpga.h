#pragma once
#include "boards/pico_ice.h"

/*
 * Low-level API for interacting with the FPGA chip.
 */

void fpga_init_clock(uint8_t mhz);
/*
 * Initialise the FPGA clock at the given frequency.
 *
 * :param mhz: The clock speed in MHz. Valid values: 48MHz, 24MHz, 16MHz 12MHz, 8MHz, 6MHz, 4MHz, 3MHz, 2MHz, 1MHz.
 */

void fpga_init_uart(uint32_t mhz);
/*
 * Initialise the UART peripheral for communication with the FPGA, at the given baudrate.
 *
 * :param mhz: The baud rate speed in MHz. Can be any value supported by the pico-sdk.
 */
