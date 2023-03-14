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
#define ICE_FPGA_35_PIN                 24
#define ICE_FPGA_27_PIN                 0
#define ICE_FPGA_25_PIN                 1
#define ICE_FPGA_21_PIN                 2
#define ICE_FPGA_19_PIN                 3
#define ICE_FPGA_26_PIN                 4
#define ICE_FPGA_23_PIN                 5
#define ICE_FPGA_20_PIN                 6
#define ICE_FPGA_18_PIN                 7

// ICE40 FPGA IO (SILICON DIE NAMES)
#define ICE_FPGA_IOB_6a                 ICE_FPGA_2_PIN
#define ICE_FPGA_IOB_9b                 ICE_FPGA_3_PIN
#define ICE_FPGA_IOB_8a                 ICE_FPGA_4_PIN
#define ICE_FPGA_IOB_13b                ICE_FPGA_6_PIN
#define ICE_FPGA_IOB_16a                ICE_FPGA_9_PIN
#define ICE_FPGA_IOB_18a                ICE_FPGA_10_PIN
#define ICE_FPGA_IOB_20a                ICE_FPGA_11_PIN
#define ICE_FPGA_IOB_31b                ICE_FPGA_18_PIN
#define ICE_FPGA_IOB_29b                ICE_FPGA_19_PIN
#define ICE_FPGA_IOB_25b                ICE_FPGA_20_PIN
#define ICE_FPGA_IOT_23b                ICE_FPGA_21_PIN
#define ICE_FPGA_IOT_37a                ICE_FPGA_23_PIN
#define ICE_FPGA_IOT_36b                ICE_FPGA_25_PIN
#define ICE_FPGA_IOT_39a                ICE_FPGA_26_PIN
#define ICE_FPGA_IOT_38b                ICE_FPGA_27_PIN
#define ICE_FPGA_IOT_41a                ICE_FPGA_28_PIN
#define ICE_FPGA_IOT_42b                ICE_FPGA_31_PIN
#define ICE_FPGA_IOT_43a                ICE_FPGA_32_PIN
#define ICE_FPGA_IOT_44b                ICE_FPGA_34_PIN
#define ICE_FPGA_IOT_46b                ICE_FPGA_35_PIN
#define ICE_FPGA_IOT_48b                ICE_FPGA_36_PIN
#define ICE_FPGA_IOT_50b                ICE_FPGA_38_PIN
#define ICE_FPGA_IOT_51a                ICE_FPGA_42_PIN
#define ICE_FPGA_IOT_49a                ICE_FPGA_43_PIN
#define ICE_FPGA_IOB_3b                 ICE_FPGA_44_PIN
#define ICE_FPGA_IOB_5b                 ICE_FPGA_45_PIN
#define ICE_FPGA_IOB_0a                 ICE_FPGA_46_PIN
#define ICE_FPGA_IOB_2b                 ICE_FPGA_47_PIN
#define ICE_FPGA_IOB_4a                 ICE_FPGA_48_PIN
#define ICE_FPGA_IOB_22a                ICE_FPGA_12_PIN
#define ICE_FPGA_IOB_24a                ICE_FPGA_13_PIN
#define ICE_FPGA_IOB_18a                ICE_FPGA_10_PIN
#define ICE_FPGA_IOB_32a                ICE_FPGA_14_PIN
#define ICE_FPGA_IOB_33b                ICE_FPGA_17_PIN
#define ICE_FPGA_IOB_34a                ICE_FPGA_15_PIN
#define ICE_FPGA_IOB_35b                ICE_FPGA_16_PIN
#define ICE_FPGA_IOT_45a                ICE_FPGA_37_PIN

// ICE_PMOD2A (near LED, shared with iCE40) top row
// GPIO
#define ICE_PMOD2A_IO4                  ICE_FPGA_19_PIN
#define ICE_PMOD2A_IO3                  ICE_FPGA_21_PIN
#define ICE_PMOD2A_IO2                  ICE_FPGA_25_PIN
#define ICE_PMOD2A_IO1                  ICE_FPGA_27_PIN
// I2C
#define ICE_PMOD2A_SDA                  ICE_PMOD2A_IO4
#define ICE_PMOD2A_SCL                  ICE_PMOD2A_IO3
#define ICE_PMOD2A_RST                  ICE_PMOD2A_IO2
#define ICE_PMOD2A_INT                  ICE_PMOD2A_IO1
// I2S
#define ICE_PMOD2A_BCLK                 ICE_PMOD2A_IO4
#define ICE_PMOD2A_ADC                  ICE_PMOD2A_IO3
#define ICE_PMOD2A_DAC                  ICE_PMOD2A_IO2
#define ICE_PMOD2A_LRCLK                ICE_PMOD2A_IO1
// SPI
#define ICE_PMOD2A_SCK                  ICE_PMOD2A_IO4
#define ICE_PMOD2A_MISO                 ICE_PMOD2A_IO3
#define ICE_PMOD2A_MOSI                 ICE_PMOD2A_IO2
#define ICE_PMOD2A_CS                   ICE_PMOD2A_IO1
// UART
#define ICE_PMOD2A_RTS                  ICE_PMOD2A_IO4
#define ICE_PMOD2A_RXD                  ICE_PMOD2A_IO3
#define ICE_PMOD2A_TXD                  ICE_PMOD2A_IO2
#define ICE_PMOD2A_CTS                  ICE_PMOD2A_IO1
// HBridge
#define ICE_PMOD2A_SB                   ICE_PMOD2A_IO4
#define ICE_PMOD2A_SA                   ICE_PMOD2A_IO3
#define ICE_PMOD2A_EN                   ICE_PMOD2A_IO2
#define ICE_PMOD2A_DIR                  ICE_PMOD2A_IO1

// ICE_PMOD2B (near LED, shared with iCE40) bottom row
// GPIO
#define ICE_PMOD2B_IO4                  ICE_FPGA_18_PIN
#define ICE_PMOD2B_IO3                  ICE_FPGA_20_PIN
#define ICE_PMOD2B_IO2                  ICE_FPGA_23_PIN
#define ICE_PMOD2B_IO1                  ICE_FPGA_26_PIN
// I2C
#define ICE_PMOD2B_SDA                  ICE_PMOD2B_IO4
#define ICE_PMOD2B_SCL                  ICE_PMOD2B_IO3
#define ICE_PMOD2B_RST                  ICE_PMOD2B_IO2
#define ICE_PMOD2B_INT                  ICE_PMOD2B_IO1
// I2S
#define ICE_PMOD2B_BCLK                 ICE_PMOD2B_IO4
#define ICE_PMOD2B_ADC                  ICE_PMOD2B_IO3
#define ICE_PMOD2B_DAC                  ICE_PMOD2B_IO2
#define ICE_PMOD2B_LRCLK                ICE_PMOD2B_IO1
// SPI
#define ICE_PMOD2B_SCK                  ICE_PMOD2B_IO4
#define ICE_PMOD2B_MISO                 ICE_PMOD2B_IO3
#define ICE_PMOD2B_MOSI                 ICE_PMOD2B_IO2
#define ICE_PMOD2B_CS                   ICE_PMOD2B_IO1
// UART
#define ICE_PMOD2B_RTS                  ICE_PMOD2B_IO4
#define ICE_PMOD2B_RXD                  ICE_PMOD2B_IO3
#define ICE_PMOD2B_TXD                  ICE_PMOD2B_IO2
#define ICE_PMOD2B_CTS                  ICE_PMOD2B_IO1
// HBridge
#define ICE_PMOD2B_SB                   ICE_PMOD2B_IO4
#define ICE_PMOD2B_SA                   ICE_PMOD2B_IO3
#define ICE_PMOD2B_EN                   ICE_PMOD2B_IO2
#define ICE_PMOD2B_DIR                  ICE_PMOD2B_IO1

// ICE_PMOD3B (near USB) top row
// GPIO
#define ICE_PMOD3A_IO4                  19
#define ICE_PMOD3A_IO3                  18
#define ICE_PMOD3A_IO2                  17
#define ICE_PMOD3A_IO1                  16
// I2C
#define ICE_PMOD3B_SDA                  ICE_PMOD3B_IO4
#define ICE_PMOD3B_SCL                  ICE_PMOD3B_IO3
#define ICE_PMOD3B_RST                  ICE_PMOD3B_IO2
#define ICE_PMOD3B_INT                  ICE_PMOD3B_IO1
// I2S
#define ICE_PMOD3B_BCLK                 ICE_PMOD3B_IO4
#define ICE_PMOD3B_ADC                  ICE_PMOD3B_IO3
#define ICE_PMOD3B_DAC                  ICE_PMOD3B_IO2
#define ICE_PMOD3B_LRCLK                ICE_PMOD3B_IO1
// SPI
#define ICE_PMOD3B_SCK                  ICE_PMOD3B_IO4
#define ICE_PMOD3B_MISO                 ICE_PMOD3B_IO3
#define ICE_PMOD3B_MOSI                 ICE_PMOD3B_IO2
#define ICE_PMOD3B_CS                   ICE_PMOD3B_IO1
// UART
#define ICE_PMOD3B_RTS                  ICE_PMOD3B_IO4
#define ICE_PMOD3B_RXD                  ICE_PMOD3B_IO3
#define ICE_PMOD3B_TXD                  ICE_PMOD3B_IO2
#define ICE_PMOD3B_CTS                  ICE_PMOD3B_IO1
// HBridge
#define ICE_PMOD3B_SB                   ICE_PMOD3B_IO4
#define ICE_PMOD3B_SA                   ICE_PMOD3B_IO3
#define ICE_PMOD3B_EN                   ICE_PMOD3B_IO2
#define ICE_PMOD3B_DIR                  ICE_PMOD3B_IO1

// ICE_PMOD3B (near USB) bottom row
// GPIO
#define ICE_PMOD3B_IO4                  23
#define ICE_PMOD3B_IO3                  22
#define ICE_PMOD3B_IO2                  21
#define ICE_PMOD3B_IO1                  20
// I2C
#define ICE_PMOD3B_SDA                  ICE_PMOD3B_IO4
#define ICE_PMOD3B_SCL                  ICE_PMOD3B_IO3
#define ICE_PMOD3B_RST                  ICE_PMOD3B_IO2
#define ICE_PMOD3B_INT                  ICE_PMOD3B_IO1
// I2S
#define ICE_PMOD3B_BCLK                 ICE_PMOD3B_IO4
#define ICE_PMOD3B_ADC                  ICE_PMOD3B_IO3
#define ICE_PMOD3B_DAC                  ICE_PMOD3B_IO2
#define ICE_PMOD3B_LRCLK                ICE_PMOD3B_IO1
// SPI
#define ICE_PMOD3B_SCK                  ICE_PMOD3B_IO4
#define ICE_PMOD3B_MISO                 ICE_PMOD3B_IO3
#define ICE_PMOD3B_MOSI                 ICE_PMOD3B_IO2
#define ICE_PMOD3B_CS                   ICE_PMOD3B_IO1
// UART
#define ICE_PMOD3B_RTS                  ICE_PMOD3B_IO4
#define ICE_PMOD3B_RXD                  ICE_PMOD3B_IO3
#define ICE_PMOD3B_TXD                  ICE_PMOD3B_IO2
#define ICE_PMOD3B_CTS                  ICE_PMOD3B_IO1
// HBridge
#define ICE_PMOD3B_SB                   ICE_PMOD3B_IO4
#define ICE_PMOD3B_SA                   ICE_PMOD3B_IO3
#define ICE_PMOD3B_EN                   ICE_PMOD3B_IO2
#define ICE_PMOD3B_DIR                  ICE_PMOD3B_IO1

#endif
