/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 * Copyright (c) 2023 TinyVision.ai Inc.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

// -----------------------------------------------------
// NOTE: THIS HEADER IS ALSO INCLUDED BY ASSEMBLER SO
//       SHOULD ONLY CONSIST OF PREPROCESSOR DIRECTIVES
// -----------------------------------------------------

#ifndef PICO2_ICE_H_
#define PICO2_ICE_H_
#include "ice40up5k.h"

// For board detection
#ifndef PICO2_ICE
#define PICO2_ICE            2
#endif
#ifndef PICO_ICE_BOARD_ID
#define PICO_ICE_BOARD_ID    PICO2_ICE
#endif
#define PICO_ICE_BOARD_NAME          "pico2-ice"

// --- RP2350 VARIANT ---
#define PICO_RP2350B 1

// --- LED ---
#ifndef PICO_DEFAULT_LED_PIN
#define PICO_DEFAULT_LED_PIN 1
#endif

// --- I2C ---
#ifndef PICO_DEFAULT_I2C
#define PICO_DEFAULT_I2C 0
#endif
#ifndef PICO_DEFAULT_I2C_SDA_PIN
#define PICO_DEFAULT_I2C_SDA_PIN 12
#endif
#ifndef PICO_DEFAULT_I2C_SCL_PIN
#define PICO_DEFAULT_I2C_SCL_PIN 13
#endif

// --- SPI ---
#define PICO_DEFAULT_SPI 1 //timo foo original value 0
#define PICO_DEFAULT_SPI_SCK_PIN 34 //PICO_PMOD_A4 SCK
#define PICO_DEFAULT_SPI_TX_PIN 35 //PICO_PMOD_A2 TX
#define PICO_DEFAULT_SPI_RX_PIN 32 //PICO_PMOD_A3 RX
#define PICO_DEFAULT_CSN_PIN 33 //PICO_PMOD_A1 SSn

// --- FLASH ---
#define PICO_BOOT_STAGE2_CHOOSE_W25Q080 1
#ifndef PICO_FLASH_SIZE_BYTES
#define PICO_FLASH_SIZE_BYTES (4 * 1024 * 1024)
#endif
#ifndef PICO_FLASH_SPI_CLKDIV
#define PICO_FLASH_SPI_CLKDIV 2
#endif
#ifndef PICO_RP2350_A2_SUPPORTED
#define PICO_RP2350_A2_SUPPORTED 1
#endif

// --- BOARD SPECIFIC ---
// LED
#define ICE_LED_RED_PIN 1
#define ICE_LED_GREEN_PIN 0
#define ICE_LED_BLUE_PIN 9
// FLASH
#ifndef ICE_FLASH_SIZE_BYTES
#define ICE_FLASH_SIZE_BYTES (4 * 1024 * 1024)
#endif
// SRAM
#ifndef ICE_SRAM_SIZE_BYTES
#define ICE_SRAM_SIZE_BYTES (8 * 1024 * 1024)
#endif
// MISC
#define ICE_GPOUT_CLOCK_PIN 22 //PICO_CLKOUT
#define ICE_RESET_BUTTON_PIN 42 //ADC2|PB
// FPGA UART
#define ICE_UART_TX 255
#define ICE_UART_RX 255

#define FPGA_DATA pico2_fpga

#endif
