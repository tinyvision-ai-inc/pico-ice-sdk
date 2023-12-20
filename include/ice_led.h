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
 * @defgroup ice_led
 * @brief RGB LEDs
 * @{
 *
 * They are active-low and shared with the iCE40:
 * - A LED will be bright if either the iCE40 or RP2040 are pulling its line low.
 * - A LED will be dark if none of the iCE40 or RP2040 are pulling its line low.
 *
 * A line pulled high does not give consitent result, they are controlled with
 * high-impedance or pulled-down.
 *
 * ## Troubleshooting
 *
 * If the GPIO LEDs do not turn on.
 *
 * Unlike the Raspberry Pi Pico board, which has a green LED attached to the GPIO pin 25,
 * the pico-ice has three LEDs attached to the RP2040 GPIO13 (red), GPIO12 (green), GPIO15 (blue).
 *
 * Moreover, the leds are "active-low", so you would need to turn their pin down for them to
 * be turned on.
 *
 * Finally, the FPGA is also connected to these LEDs.
 */

#pragma once
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initialise the GPIO pins for use with open-drain LED control, shared
 *  with the iCE40.
 */
void ice_led_init(void);

/**
 * @brief Control the red LED.
 * @param state Bright if true, dark if false.
 */
void ice_led_red(bool state);

/**
 * @brief Control the green LED.
 * @param state Bright if true, dark if false.
 */
void ice_led_green(bool state);

/**
 * @brief Control the blue LED.
 * @param state Bright if true, dark if false.
 */
void ice_led_blue(bool state);

#ifdef __cplusplus
}
#endif

/** @} */
