/*
 * MIT License
 *
 * Copyright (c) 2025 tinyVision.ai
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

#include <stdint.h>
#include <errno.h>

#define ICE_HAL_ATTR __attribute__((weak))

/** @ingroup SPI HAL functions
 *  @{
 */

/**
 * @brief This hal function must initialize standard SPI at a certain speed and
 * with a specific pin setup, on RP2 this might mean loading a PIO
 * to provide the inverted mosi to miso for CRAM.
 * A pin number of -1 on miso means no miso pin necessary.
 * SPI device CS must be controllable via GPIO.
 *
 * @param mosi MOSI pin
 * @param miso MISO pin
 * @param clk CLOCK pin
 * @param freq SPI frequency
 * @returns negative in case of failure, or a SPI device ID
 */

int ICE_HAL_ATTR ice_hal_spi_init(int mosi, int miso, int clk, int freq);

/**
 * @brief This hal function must write data on SPI device ID in a blocking way
 * @param buf data buffer
 * @param len size of data
 * @returns negative In case of failure, and in case of success, 0 or the amount
 * of data written
 */

int ICE_HAL_ATTR ice_hal_spi_write(uint8_t *buf, size_t len);

/**
 * @brief This hal function must read data on SPI device ID in a blocking way
 * @param buf data buffer
 * @param len maximum amount of data to read
 * @returns negative In case of failure, or the amount of data read
 */

int ICE_HAL_ATTR ice_hal_spi_read(uint8_t *buf, int len);

/**
 * @brief This hal function must declare the SPI device corresponding to the ID
 * as freed from the HAL's control
 *
 * @returns negative In case of failure, or 0
 */

int ICE_HAL_ATTR ice_hal_spi_deinit(void);

/** @}*/

/** @ingroup GPIO HAL functions
 *  @{
 */

/**
 * @brief This hal function must initialize GPIO control on the specific pin.
 * High-Z (High-Impedance) default is preferred.
 *
 * @param gpio gpio pin ID
 * @returns negative In case of failure, or 0
 */

int ICE_HAL_ATTR ice_hal_gpio_init(int gpio);

/**
 * @brief This hal function must set GPIO as High Impedance and discard
 * Pull-Up and Pull-Down Settings.
 *
 * @param gpio gpip pin ID
 * @returns negative In case of failure, or 0
 */

int ICE_HAL_ATTR ice_hal_gpio_set_high_z(int gpio);

/**
 * @brief This hal function must set GPIO as Pull-Up.
 *
 * @param gpio gpio pin ID
 * @returns negative In case of failure, or 0
 */

int ICE_HAL_ATTR ice_hal_gpio_set_pu(int gpio);

/**
 * @brief This hal function must set GPIO as Pull-Down.
 *
 * @param gpio gpio pin ID
 * @returns negative In case of failure, or 0
 */

int ICE_HAL_ATTR ice_hal_gpio_set_pd(int gpio);

/**
 * @brief This hal function must set GPIO as On/1.
 * This may discard High-Impedance setting.
 *
 * @param gpio gpio pin ID
 * @returns negative In case of failure, or 0
 */

int ICE_HAL_ATTR ice_hal_gpio_set_1(int gpio);

/**
 * @brief This hal function must set GPIO as Off/0.
 * This may discard High-Impedance setting.
 *
 * @param gpio gpio pin ID
 * @returns negative In case of failure, or 0
 */

int ICE_HAL_ATTR ice_hal_gpio_set_0(int gpio);

/**
 * @brief This hal function must return control of the GPIO pin from the HAL
 *
 * @param gpio gpio pin ID
 * @returns negative In case of failure, or 0
 */

int ICE_HAL_ATTR ice_hal_gpio_deinit(int gpio);

/** @}*/
