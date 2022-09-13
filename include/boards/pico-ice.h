// Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
// Copyright (c) 2022 tinyvision-ai-inc
//
// SPDX-License-Identifier: BSD-3-Clause
//
// -----------------------------------------------------
// NOTE: THIS HEADER IS ALSO INCLUDED BY ASSEMBLER SO
//       SHOULD ONLY CONSIST OF PREPROCESSOR DIRECTIVES
// -----------------------------------------------------

#ifndef _BOARDS_ICE_H
#define _BOARDS_ICE_H

/*
 * Specific to pico-ice
 */

#define ICE_LED_RED_PIN 22
/*
 * Red LED control pin of the RGB led.
 */

#define ICE_LED_GREEN_PIN 23
/*
 * Green LED control pin of the RGB led.
 */

#define ICE_LED_BLUE_PIN 24
/*
 * Blue LED control pin of the RGB led.
 */

/*
 * Pinout between the RP2040 and the FPGA's flash chip.
 * These pins must be set at high-impedance/floating whenever not in use to program the flash chip,
 * to not distrub the FPGA operation, in particular when the FPGA is under initialisation.
 */

#define ICE_FLASH_SPI_SCK_PIN 2
/*
 * Configured as SPI FUNCSEL by ``ice_init_flash()``.
 */

#define ICE_FLASH_SPI_TX_PIN 3
/*
 * Configured as SPI FUNCSEL by ``ice_init_flash()``.
 */

#define ICE_FLASH_SPI_RX_PIN 0
/*
 * Configured as SPI FUNCSEL by ``ice_init_flash()``.
 */

#define ICE_FLASH_SPI_CSN_PIN 1
/*
 * It is configured as GPIO FUNCSEL by ``ice_init_flash()``,
 * and controlled by the flash library.
 */

#define ICE_FPGA_CLOCK_PIN 25
/*
 * The RP2040 pin at which a clock signal is sent, as a source for the ICE40 system clock.
 */

#define TINYVISION_AI_INC_PICO_ICE
/*
 * To use for board-detection.
 */

/*
 * UART
 * ~~~~
 */
#ifndef PICO_DEFAULT_UART
#define PICO_DEFAULT_UART 0
/*
 * Same as the pico-sdk: stdio_init_all() will enable this UART0.
 */
#endif
#ifndef PICO_DEFAULT_UART_TX_PIN
#define PICO_DEFAULT_UART_TX_PIN 16
/*
 * Different than boards/pico.h: same physical location, different GPIO pin.
 */
#endif
#ifndef PICO_DEFAULT_UART_RX_PIN
#define PICO_DEFAULT_UART_RX_PIN 17
/*
 * Different than boards/pico.h: same physical location, different GPIO pin.
 */
#endif

/*
 * LED
 * ~~~
 */
#ifndef PICO_DEFAULT_LED_PIN
#define PICO_DEFAULT_LED_PIN 23
/*
 * The GPIO25 used by pico-sdk is used for sending the clock over to the FPGA.
 * There are three LED pins (RGB): GPIO22 (red), GPIO23 (green), GPIO24 (blue).
 */
#endif
// no PICO_DEFAULT_WS2812_PIN

/*
 * I2C
 * ~~~
 */
#ifndef PICO_DEFAULT_I2C
#define PICO_DEFAULT_I2C 0
#endif
#ifndef PICO_DEFAULT_I2C_SDA_PIN
#define PICO_DEFAULT_I2C_SDA_PIN 4
#endif
#ifndef PICO_DEFAULT_I2C_SCL_PIN
#define PICO_DEFAULT_I2C_SCL_PIN 5
#endif

/*
 * SPI
 * ~~~
 */
#ifndef PICO_DEFAULT_SPI
#define PICO_DEFAULT_SPI 0
/*
 * The communication with the flash is done via SPI1,
 * letting SPI0 for the user like in the pico-sdk.
 * The pinout is unchanged.
 */

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

/*
 * FLASH
 * ~~~~~
 *
 * This is the internal flash used by the RP2040 chip,
 * not the flash used by the ICE40 FPGA.
 */

#define PICO_BOOT_STAGE2_CHOOSE_W25Q080 1
/*
 * The pico-ice uses the same chip except with a larger size, and it also supports QSPI:
 * https://github.com/raspberrypi/pico-sdk/blob/master/src/rp2_common/boot_stage2/boot2_w25q080.S
 */

#ifndef PICO_FLASH_SPI_CLKDIV
#define PICO_FLASH_SPI_CLKDIV 2
/*
 * The pico-ice has the same flash chip family as the pico with the same clock speed.
 */
#endif

#ifndef PICO_FLASH_SIZE_BYTES
#define PICO_FLASH_SIZE_BYTES (4 * 1024 * 1024)
/*
 * The flash chip is W25Q32JVSSIQ: twice larger than the pico.
 */
#endif

#define PICO_SMPS_MODE_PIN 15
/*
 * Changed from the default pico-board to not enable it at all time (due to the RGB LED driving it up).
 * Drive high to force power supply into PWM mode (lower ripple on 3V3 at light loads)
 * It is the PICO_PMOD_A4 pin.
 */

#ifndef PICO_RP2040_B0_SUPPORTED
#define PICO_RP2040_B0_SUPPORTED 1
/*
 * Nearly all RP2040 chips sold on 2022 are B0 or B1 iterations, so B0 features are guaranteed to be supported.
 */
#endif

#endif
