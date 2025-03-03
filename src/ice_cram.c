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

#include "hardware/pio.h"
#include "pico/time.h"
#include "boards.h"
#include "ice_HAL.h"
#include "ice_fpga.h"
#include "ice_cram.pio.h"

static ice_fpga fpga_copy;
static bool fpga_initialized = false;


bool ice_cram_open(const ice_fpga fpga)
{
    uint8_t tmp = 0;
    int ret;

    if (fpga_initialized) return false;
    fpga_copy = fpga;
    fpga_copy.bus = fpga.bus;

    // Hold FPGA in reset before doing anything with SPI bus.
    ret = ice_fpga_stop(fpga);
    if (ret < 0)
        return ret;

    ret = ice_hal_spi_init(fpga_copy.bus.MISO, -1, fpga_copy.bus.SCK, 1000000);
    if (ret < 0)
        return ret;

    // SPI_SS low signals FPGA to receive the bitstream.
    ice_hal_gpio_init(fpga_copy.bus.CS_cram);
    ice_hal_gpio_set_0(fpga_copy.bus.CS_cram);

    // Bring FPGA out of reset after at least 200ns.
    busy_wait_us(2);
    ice_hal_gpio_set_1(fpga_copy.pin_creset);

    // At least 1200us for FPGA to clear internal configuration memory.
    busy_wait_us(1300);

    // SPI_SS high for 8 SPI_SCLKs
    ice_hal_gpio_set_1(fpga_copy.bus.CS_cram);
    ice_hal_spi_write(&tmp, 1);
    ice_hal_gpio_set_0(fpga_copy.bus.CS_cram);

    fpga_initialized = true;

    return true;
}

bool ice_cram_write(const uint8_t* bitstream, uint32_t size)
{
    return ice_hal_spi_write(bitstream, size);
}

bool ice_cram_close(void)
{
    uint8_t tmp[7] = {0};

    if (!fpga_initialized) return false;


    // Bring SPI_SS high at end of bitstream and leave it pulled up.
    ice_hal_gpio_set_1(fpga_copy.bus.CS_cram);
    sleep_us(1);
    ice_hal_gpio_set_pu(fpga_copy.bus.CS_cram);
    ice_hal_gpio_set_high_z(fpga_copy.bus.CS_cram);

    // Output dummy bytes. CDONE should go high within 100 SCLKs or there was an error with the bitstream.
    for (int i = 0; i < 13; ++i) {
        ice_hal_spi_write(tmp, 1);
        if (ice_hal_gpio_get(fpga_copy.pin_cdone)) {
            break;
        }
    }

    // At least another 49 SCLK cycles once CDONE goes high.
    ice_hal_spi_write(tmp, 7);

    ice_hal_spi_deinit();

    fpga_initialized = false;

    return ice_hal_gpio_get(fpga_copy.pin_creset);
}
