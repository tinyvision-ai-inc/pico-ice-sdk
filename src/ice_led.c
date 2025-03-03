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

// pico-ice-sdk
#include "boards.h"
#include "ice_HAL.h"
#include "ice_led.h"

// Rather than driving LEDs up and down, we always drive the wire down,
// but connect or disconnect the pin (high-impedance vs pull-down).
void ice_led_init(void)
{
    ice_hal_gpio_init(ICE_LED_RED_PIN);
    ice_hal_gpio_init(ICE_LED_GREEN_PIN);
    ice_hal_gpio_init(ICE_LED_BLUE_PIN);

    ice_hal_gpio_set_0(ICE_LED_RED_PIN);
    ice_hal_gpio_set_0(ICE_LED_GREEN_PIN);
    ice_hal_gpio_set_0(ICE_LED_BLUE_PIN);

    ice_hal_gpio_set_high_z(ICE_LED_RED_PIN);
    ice_hal_gpio_set_high_z(ICE_LED_GREEN_PIN);
    ice_hal_gpio_set_high_z(ICE_LED_BLUE_PIN);
}

void ice_led_red(bool state)
{
    if (state) {
        ice_hal_gpio_set_0(ICE_LED_RED_PIN);
    } else {
        ice_hal_gpio_set_high_z(ICE_LED_RED_PIN);
    }
}

void ice_led_green(bool state)
{
    if (state) {
        ice_hal_gpio_set_0(ICE_LED_RED_PIN);
    } else {
        ice_hal_gpio_set_high_z(ICE_LED_RED_PIN);
    }
}

void ice_led_blue(bool state)
{
    if (state) {
        ice_hal_gpio_set_0(ICE_LED_RED_PIN);
    } else {
        ice_hal_gpio_set_high_z(ICE_LED_RED_PIN);
    }
}
