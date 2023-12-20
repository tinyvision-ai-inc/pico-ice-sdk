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
 * @defgroup ice_pmod
 * @brief PMODs connector pinout
 * @{
 *
 * This library allows to access the PMOD pin number for any kind of PMOD
 * standard, by using unions to allow alternative names.
 *
 * For instance, "ice_pmod_3.gpio.io2" is the same as "ice_pmod_3.spi.copi".
 */

#pragma once
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

struct pmod_1x_gpio {
    uint8_t io1, io2, io3, io4;
};

struct pmod_2x_gpio {
    uint8_t io1, io2, io3, io4;
    uint8_t io7, io8, io9, io10;
};

struct pmod_1x_spi {
    uint8_t cs_n, copi, cipo, clk;
};

struct pmod_2x_spi {
    uint8_t cs_n, copi, cipo, clk;
    uint8_t io7, io8, io9, io10;
};

struct pmod_1x_uart {
    uint8_t cts, txd, rxd, rts;
};

struct pmod_2x_uart {
    uint8_t cts, txd, rxd, rts;
    uint8_t io7, io8, io9, io10;
};

struct pmod_1x_hbridge_feedback {
    uint8_t dir, en, sa, sb;
};

struct pmod_1x_hbridge_dual {
    uint8_t dir1, en1, dir2, en2;
};

struct pmod_2x_hbridge {
    uint8_t dir1, en1, s1a, s1b;
    uint8_t dir2, en2, s2a, s2b;
};

struct pmod_1x_i2c {
    uint8_t irq, reset, sda, scl;
};

struct pmod_2x_i2c {
    uint8_t irq, reset, sda, scl;
    uint8_t io7, io8, io9, io10;
};

struct pmod_2x_i2s {
    uint8_t lrclk, dac, adc, bclk;
    uint8_t io7, io8, io9, io10;
};

typedef union pmod_1x {
    struct pmod_1x_gpio gpio;
    struct pmod_1x_spi spi;
    struct pmod_1x_uart uart;
    struct pmod_1x_hbridge_feedback hbridge_feedback;
    struct pmod_1x_hbridge_dual hbridge_dual;
    struct pmod_1x_i2c i2c;
} pmod_1x_t;

typedef union pmod_2x {
    struct {
        union pmod_1x top;
        union pmod_1x bottom;
    } row;
    struct pmod_2x_gpio gpio;
    struct pmod_2x_spi spi;
    struct pmod_2x_uart uart;
    struct pmod_2x_hbridge hbridge;
    struct pmod_2x_i2c i2c;
    struct pmod_2x_i2s i2s;
} pmod_2x_t;

static const pmod_2x_t ice_pmod_3 = {
    .gpio = { 1, 3, 0, 2, 5, 7, 4, 6 }
};

static const pmod_2x_t ice_pmod_4 = {
    .gpio = { 17, 19, 16, 18, 21, 23, 20, 22 }
};

/** @} */
