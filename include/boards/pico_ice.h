// Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
// Copyright (c) 2022 tinyvision-ai-inc
//
// SPDX-License-Identifier: BSD-3-Clause
//
// -----------------------------------------------------
// NOTE: THIS HEADER IS ALSO INCLUDED BY ASSEMBLER SO
//       SHOULD ONLY CONSIST OF PREPROCESSOR DIRECTIVES
// -----------------------------------------------------

#ifndef BOARDS_PICO_ICE_H
#define BOARDS_PICO_ICE_H

// Specific to pico-ice

/** Red LED control pin of the RGB led. */
#define ICE_LED_RED_PIN 13

/** Green LED control pin of the RGB led. */
#define ICE_LED_GREEN_PIN 12

/** Blue LED control pin of the RGB led. */
#define ICE_LED_BLUE_PIN 15

/** Pinout between the RP2040 and the FPGA's UART port. */
#define ICE_FPGA_UART_TX_PIN 0
#define ICE_FPGA_UART_RX_PIN 1

/** The RP2040 pin at which a clock signal is sent, as a source for the ICE40 system clock. */
#define ICE_FPGA_CLOCK_PIN 25

/** The RP2040 pin for exporting a clock to an external header. */
#define ICE_CLOCK_OUT_PIN 24

/** The size of the W25Q32JVSSIQ flash chip also connected to the FPGA. */
#define ICE_FPGA_FLASH_SIZE_BYTES (4 * 1024 * 1024)

/** Instance number of the UART connected to the FPGA */
#define ICE_FPGA_UART 1

/** IRQ number for the UART instace connected to the FPGA */
#define ICE_FPGA_UART_IRQ __CONCAT(__CONCAT(UART, ICE_FPGA_UART), _IRQ)

/** UART interface transferring everything received over an USB UART interface (USB CDC ACM). */
#define uart_fpga __CONCAT(uart, ICE_FPGA_UART)

#define ICE_FPGA_CDONE_PIN 26
#define ICE_FPGA_CRESET_PIN 27

// Pinout between the RP2040 and the FPGA's flash chip.
// These pins must be set at high-impedance/floating whenever not in use to program the flash chip,
// to not distrub the FPGA operation, in particular when the FPGA is under initialisation.

/** Configured as SPI FUNCSEL by ``ice_init_flash()``. */
#define ICE_FLASH_SPI_SCK_PIN 10

/** Configured as SPI FUNCSEL by ``ice_init_flash()``. */
#define ICE_FLASH_SPI_TX_PIN 11

/** Configured as SPI FUNCSEL by ``ice_init_flash()``. */
#define ICE_FLASH_SPI_RX_PIN 8

/** Configured as GPIO FUNCSEL by ``ice_init_flash()``. Controlled by the flash library. */
#define ICE_FLASH_SPI_CSN_PIN 9

/** To use for board-detection. */
#define TINYVISION_AI_INC_PICO_ICE

// UART

/** Same as the pico-sdk: stdio_init_all() will enable this UART0. */
#ifndef PICO_DEFAULT_UART
#define PICO_DEFAULT_UART 0
#endif

/** Different than boards/pico.h: same physical location, different GPIO pin. */
#ifndef PICO_DEFAULT_UART_TX_PIN
#define PICO_DEFAULT_UART_TX_PIN 12
#endif

/** Different than boards/pico.h: same physical location, different GPIO pin. */
#ifndef PICO_DEFAULT_UART_RX_PIN
#define PICO_DEFAULT_UART_RX_PIN 13
#endif

// LED

/** The GPIO25 used by pico-sdk is used for sending the clock over to the FPGA.
 * There are three LED pins (RGB): GPIO22 (red), GPIO23 (green), GPIO24 (blue). */
#ifndef PICO_DEFAULT_LED_PIN
#define PICO_DEFAULT_LED_PIN 15
#endif

// no PICO_DEFAULT_WS2812_PIN

// I2C

#ifndef PICO_DEFAULT_I2C
#define PICO_DEFAULT_I2C 0
#endif

#ifndef PICO_DEFAULT_I2C_SDA_PIN
#define PICO_DEFAULT_I2C_SDA_PIN 12
#endif

#ifndef PICO_DEFAULT_I2C_SCL_PIN
#define PICO_DEFAULT_I2C_SCL_PIN 13
#endif

// SPI

/** Communication with flash is done via SPI1, SPI0 kept for the user like in the pico-sdk.
 * The pinout is unchanged. */
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

// FLASH
// This is the internal flash used by the RP2040 chip,
// not the flash used by the ICE40 FPGA.

/** The flash peripheral instance that is connected to the FGPA's flash chip. */
#define spi_fpga_flash          NULL // spi1

/** The pico-ice uses the same chip except with a larger size, and it also supports QSPI:
 * https://github.com/raspberrypi/pico-sdk/blob/master/src/rp2_common/boot_stage2/boot2_w25q080.S */
#define PICO_BOOT_STAGE2_CHOOSE_W25Q080 1

/** The pico-ice has the same flash chip family as the pico with the same clock speed. */
#ifndef PICO_FLASH_SPI_CLKDIV
#define PICO_FLASH_SPI_CLKDIV 2
#endif

/** The flash chip is W25Q32JVSSIQ: twice larger than the pico. */
#ifndef PICO_FLASH_SIZE_BYTES
#define PICO_FLASH_SIZE_BYTES (4 * 1024 * 1024)
#endif

/** Changed from the default pico-board to not enable it at all time (due to the RGB LED driving it up).
 * Drive high to force power supply into PWM mode (lower ripple on 3V3 at light loads)
 * It is the PICO_PMOD_A4 pin. */
#define PICO_SMPS_MODE_PIN 15

/** Nearly all RP2040 chips sold on 2022 are B0 or B1 iterations, so B0 features are guaranteed to be supported. */
#ifndef PICO_RP2040_B0_SUPPORTED
#define PICO_RP2040_B0_SUPPORTED 1
#endif

#endif
