/*
 * MIT License
 * 
 * Copyright (c) 2023 tinyVision.ai
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/**
 * @defgroup ice_spi
 * @brief Main SPI bus I/O
 * @{
 *
 * SPI library exclusive to the main SPI bus between the RP2040 and the various
 * other board components, including the iCE40 CRAM, iCE40 hardened SPI core,
 * SRAM chip, FLASH chip.
 */

#pragma once
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

/**
 * @brief This is chosen to allow all commands to the flash and SRAM to work.
 *
 * 33MHz is the fastest the SRAM supports a 03h read command.
 */
#define ICE_SPI_BAUDRATE (33 * 1000 * 1000)

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Configure the GPIO pins of the SPI library to high-impedance
 *
 * This lets others access the bus, such as the iCE40 during initial
 * configuration.
 */
void ice_spi_init(void);

void ice_spi_init_cs_pin(uint8_t cs_pin, bool active_high);

/**
 * @brief Sets the SPI chip select pin to low state.
 * @param csn_pin User-selectable GPIO pin to assert, set to LOW voltage level.
 * @param active_high true for active-high chip-select pin, false for
 *  active-low.
 *
 * Also set the SPI TX and SCK pins to output/drive mode, and keeps the RX pin to input/high-z mode.
 */
void ice_spi_chip_select(uint8_t cs_pin);

/**
 * @brief Sets the SPI chip select pin to high state.
 * @param csn_pin User-selectable GPIO pin to assert, set to LOW voltage level.
 *
 * Also set the SPI TX and SCK pins back to input/high-z mode.
 */
void ice_spi_chip_deselect(uint8_t csn_pin);

/**
 * @brief Wait previous transfer completion if any and enqueue a new one in the background (interrupt-driven).
 * @param buf buffer to send over SPI.
 * @param len size of that buffer.
 * @param callback function called at the end of the transfer.
 * @param context argument passed to that function.
 * 
 * If callback is NULL, then nothing will be done.
 */
void ice_spi_write_async(const uint8_t *data, size_t data_size, void (*callback)(volatile void *), void *context);

/**
 * @brief Blocking version of ice_spi_write_async().
 * @param buf Buffer to send over SPI.
 * @param len Size of that buffer.
 */
void ice_spi_write_blocking(const uint8_t *data, size_t data_size);

/**
 * @brief Wait previous transfer completion if any and enqueue a new one in the
 *  background (interrupt-driven).
 * @param tx Byte to send conotinuously while readying
 * @param buf Buffer to fill from SPI.
 * @param len Size of that buffer.
 * @param callback Function called at the end of the transfer.
 * @param context Argument passed to that function.
 *
 * If `callback` is `NULL`, then nothing will be done.
 */
void ice_spi_read_async(uint8_t *data, size_t data_size, void (*callback)(volatile void *), void *context);

/**
 * @brief Blocking version of ice_spi_read_async().
 * @param tx Byte to send conotinuously while readying
 * @param buf Buffer to fill from SPI.
 * @param len Size of that buffer.
 */
void ice_spi_read_blocking(uint8_t *data, size_t data_size);

/**
 * @brief Checks for compmletion of the current async operation.
 * @return True if an SPI transfer is ongoing, false if ready to enqueue another.
 */
bool ice_spi_is_async_complete(void);

/**
 * @brief Waits until SPI transfer commpletes.
 */
void ice_spi_wait_completion(void);

#ifdef __cplusplus
}
#endif

/** @} */
