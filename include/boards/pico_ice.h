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

#ifndef _BOARDS_PICO_ICE_H
#define _BOARDS_PICO_ICE_H

// For board detection
#define TINYVISION_AI_INC_PICO_ICE

// --- UART ---
#ifndef PICO_DEFAULT_UART
#define PICO_DEFAULT_UART 0
#endif
#ifndef PICO_DEFAULT_UART_TX_PIN
#define PICO_DEFAULT_UART_TX_PIN 0
#endif
#ifndef PICO_DEFAULT_UART_RX_PIN
#define PICO_DEFAULT_UART_RX_PIN 1
#endif

// --- LED ---
#ifndef PICO_DEFAULT_LED_PIN
#define PICO_DEFAULT_LED_PIN 15
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
#ifndef PICO_DEFAULT_SPI
#define PICO_DEFAULT_SPI 1
#endif
#ifndef PICO_DEFAULT_SPI_SCK_PIN
#define PICO_DEFAULT_SPI_SCK_PIN 18
#endif
#ifndef PICO_DEFAULT_SPI_TX_PIN
#define PICO_DEFAULT_SPI_TX_PIN 19
#endif
#ifndef PICO_DEFAULT_SPI_RX_PIN
#define PICO_DEFAULT_SPI_RX_PIN 16
#endif
#ifndef PICO_DEFAULT_SPI_CSN_PIN
#define PICO_DEFAULT_SPI_CSN_PIN 17
#endif

// --- FLASH ---

#define PICO_BOOT_STAGE2_CHOOSE_W25Q080 1

#ifndef PICO_FLASH_SIZE_BYTES
#define PICO_FLASH_SIZE_BYTES (4 * 1024 * 1024)
#endif

#ifndef PICO_FLASH_SPI_CLKDIV
#define PICO_FLASH_SPI_CLKDIV 2
#endif

#ifndef PICO_RP2040_B0_SUPPORTED
#define PICO_RP2040_B0_SUPPORTED 1
#endif

#ifndef PICO_RP2040_B1_SUPPORTED
#define PICO_RP2040_B1_SUPPORTED 0
#endif

#ifndef PICO_SMPS_MODE_PIN
#define PICO_SMPS_MODE_PIN 15
#endif

// --- BOARD SPECIFIC ---

// LED
#define ICE_LED_RED_PIN 13
#define ICE_LED_GREEN_PIN 12
#define ICE_LED_BLUE_PIN 15

// SPI
#ifndef ICE_DEFAULT_SPI
#define ICE_DEFAULT_SPI 1
#endif
#ifndef ICE_DEFAULT_SPI_RX_PIN
#define ICE_DEFAULT_SPI_RX_PIN 11
#endif
#ifndef ICE_DEFAULT_SPI_SCK_PIN
#define ICE_DEFAULT_SPI_SCK_PIN 10
#endif
#ifndef ICE_DEFAULT_SPI_TX_PIN
#define ICE_DEFAULT_SPI_TX_PIN 8
#endif
#ifndef ICE_FLASH_SPI_CSN_PIN
#define ICE_FLASH_SPI_CSN_PIN 9
#endif
#ifndef ICE_FPGA_SPI_CSN_PIN
#define ICE_FPGA_SPI_CSN_PIN 9
#endif
#ifndef ICE_SRAM_SPI_CS_PIN
#define ICE_SRAM_SPI_CS_PIN 14
#endif

// FLASH
#ifndef ICE_FLASH_SIZE_BYTES
#define ICE_FLASH_SIZE_BYTES (4 * 1024 * 1024)
#endif

// MISC
#define ICE_GPOUT_CLOCK_PIN             25
#define ICE_BUTTON_PIN                  10

// ICE40 FPGA (SYSTEM)
#ifndef ICE_FPGA_CLOCK_PIN
#define ICE_FPGA_CLOCK_PIN 24
#endif
#ifndef ICE_FPGA_CDONE_PIN
#define ICE_FPGA_CDONE_PIN 26
#endif
#ifndef ICE_FPGA_CRESET_B_PIN
#define ICE_FPGA_CRESET_B_PIN 27
#endif

// ICE40 FPGA IO (PACKAGE NAMES)
#define ICE_FPGA_27_PIN                 0
#define ICE_FPGA_25_PIN                 1
#define ICE_FPGA_21_PIN                 2
#define ICE_FPGA_19_PIN                 3
#define ICE_FPGA_26_PIN                 4
#define ICE_FPGA_23_PIN                 5
#define ICE_FPGA_20_PIN                 6
#define ICE_FPGA_18_PIN                 7

// ICE40 FPGA IO (SILICON DIE NAMES)
#define ICE_FPGA_IOB_6a_PIN             ICE_FPGA_2_PIN
#define ICE_FPGA_IOB_9b_PIN             ICE_FPGA_3_PIN
#define ICE_FPGA_IOB_8a_PIN             ICE_FPGA_4_PIN
#define ICE_FPGA_IOB_13b_PIN            ICE_FPGA_6_PIN
#define ICE_FPGA_IOB_16a_PIN            ICE_FPGA_9_PIN
#define ICE_FPGA_IOB_18a_PIN            ICE_FPGA_10_PIN
#define ICE_FPGA_IOB_20a_PIN            ICE_FPGA_11_PIN
#define ICE_FPGA_IOB_31b_PIN            ICE_FPGA_18_PIN
#define ICE_FPGA_IOB_29b_PIN            ICE_FPGA_19_PIN
#define ICE_FPGA_IOB_25b_PIN            ICE_FPGA_20_PIN
#define ICE_FPGA_IOT_23b_PIN            ICE_FPGA_21_PIN
#define ICE_FPGA_IOT_37a_PIN            ICE_FPGA_23_PIN
#define ICE_FPGA_IOT_36b_PIN            ICE_FPGA_25_PIN
#define ICE_FPGA_IOT_39a_PIN            ICE_FPGA_26_PIN
#define ICE_FPGA_IOT_38b_PIN            ICE_FPGA_27_PIN
#define ICE_FPGA_IOT_41a_PIN            ICE_FPGA_28_PIN
#define ICE_FPGA_IOT_42b_PIN            ICE_FPGA_31_PIN
#define ICE_FPGA_IOT_43a_PIN            ICE_FPGA_32_PIN
#define ICE_FPGA_IOT_44b_PIN            ICE_FPGA_34_PIN
#define ICE_FPGA_IOT_46b_PIN            ICE_FPGA_35_PIN
#define ICE_FPGA_IOT_48b_PIN            ICE_FPGA_36_PIN
#define ICE_FPGA_IOT_50b_PIN            ICE_FPGA_38_PIN
#define ICE_FPGA_IOT_51a_PIN            ICE_FPGA_42_PIN
#define ICE_FPGA_IOT_49a_PIN            ICE_FPGA_43_PIN
#define ICE_FPGA_IOB_3b_PIN             ICE_FPGA_44_PIN
#define ICE_FPGA_IOB_5b_PIN             ICE_FPGA_45_PIN
#define ICE_FPGA_IOB_0a_PIN             ICE_FPGA_46_PIN
#define ICE_FPGA_IOB_2b_PIN             ICE_FPGA_47_PIN
#define ICE_FPGA_IOB_4a_PIN             ICE_FPGA_48_PIN
#define ICE_FPGA_IOB_22a_PIN            ICE_FPGA_12_PIN
#define ICE_FPGA_IOB_24a_PIN            ICE_FPGA_13_PIN
#define ICE_FPGA_IOB_18a_PIN            ICE_FPGA_10_PIN
#define ICE_FPGA_IOB_32a_PIN            ICE_FPGA_14_PIN
#define ICE_FPGA_IOB_33b_PIN            ICE_FPGA_17_PIN
#define ICE_FPGA_IOB_34a_PIN            ICE_FPGA_15_PIN
#define ICE_FPGA_IOB_35b_PIN            ICE_FPGA_16_PIN
#define ICE_FPGA_IOT_45a_PIN            ICE_FPGA_37_PIN

#endif
