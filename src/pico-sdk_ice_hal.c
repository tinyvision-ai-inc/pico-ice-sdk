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

#include "hardware/gpio.h"
#include "hardware/pio.h"
#include "hardware/spi.h"
#include "pico/time.h"
#include "pico/stdlib.h"
#include "boards.h"

#include "ice_cram.pio.h"

#include "ice_HAL.h"


/*! Pico-SDK ice_HAL port */

/* Possible SPI definitions, from *_interface_pins.json */

typedef struct pi_spi_pins {
	const int	*miso;
	const int	miso_len;
	const int	*mosi;
	const int	mosi_len;
	const int	*clk;
	const int	clk_len;
} pi_spi_pins_t;

#define ARRAY_SIZE(foo) (sizeof(foo)/sizeof(foo[0]))

#ifdef PICO_RP2350A

const int pi_spi_pins_rx_0[] = { 0, 4, 16, 20 };
const int pi_spi_pins_tx_0[] = { 3, 7, 19, 23 };
const int pi_spi_pins_clk_0[] = { 2, 6, 18, 22 };


const int pi_spi_pins_rx_1[] = { 8, 12, 24, 28 };
const int pi_spi_pins_tx_1[] = { 11, 15, 27 };
const int pi_spi_pins_clk_1[] = { 10, 14, 26 };

#elifdef PICO_RP2350B

const int pi_spi_pins_rx_0[] = { 0, 4, 16, 20, 32, 36 };
const int pi_spi_pins_tx_0[] = { 3, 7, 19, 23, 35, 39 };
const int pi_spi_pins_clk_0[] = { 2, 6, 18, 22, 34, 38 };


const int pi_spi_pins_rx_1[] = { 8, 12, 24, 28, 40, 44 };
const int pi_spi_pins_tx_1[] = { 11, 15, 27, 31, 43, 47 };
const int pi_spi_pins_clk_1[] = { 10, 14, 26, 30, 42, 46 };

#else

const int pi_spi_pins_rx_0[] = { 0, 4, 16, 20 };
const int pi_spi_pins_tx_0[] = { 3, 7, 19, 23 };
const int pi_spi_pins_clk_0[] = { 2, 6, 18, 22 };


const int pi_spi_pins_rx_1[] = { 8, 12, 24, 28 };
const int pi_spi_pins_tx_1[] = { 11, 15, 27 };
const int pi_spi_pins_clk_1[] = { 10, 14, 26 };

#endif

static const pi_spi_pins_t pi_spi_pins_0 = {
	.miso = pi_spi_pins_rx_0,
	.miso_len = ARRAY_SIZE(pi_spi_pins_rx_0),
	.mosi = pi_spi_pins_tx_0,
	.mosi_len = ARRAY_SIZE(pi_spi_pins_tx_0),
	.clk = pi_spi_pins_clk_0,
	.clk_len = ARRAY_SIZE(pi_spi_pins_clk_0),
};

static const pi_spi_pins_t pi_spi_pins_1 = {
	.miso = pi_spi_pins_rx_1,
	.miso_len = ARRAY_SIZE(pi_spi_pins_rx_1),
	.mosi = pi_spi_pins_tx_1,
	.mosi_len = ARRAY_SIZE(pi_spi_pins_tx_1),
	.clk = pi_spi_pins_clk_1,
	.clk_len = ARRAY_SIZE(pi_spi_pins_clk_1),
};

static const pi_spi_pins_t pi_spi_pins[2] = { pi_spi_pins_0, pi_spi_pins_1 };

static int			hal_mosi;
static int			hal_miso;
static int			hal_clk;
static spi_inst_t	*device;
static bool			has_spi = false;
static bool			is_pio = false;
static PIO			pio;
static int			sm;
static uint			offset;
/* 1 Mbit/sec for debugging, could be much faster, 1Mbit/s is the minimum value */
static const int	clk_div = 1;

static bool pio_try_add_program(PIO try_pio)
{
	if (!pio_can_add_program(try_pio, &ice_cram_program)) {
		return false;
	}

	sm = pio_claim_unused_sm(try_pio, false);
	if (sm < 0) {
		return false;
	}

	pio = try_pio;
	offset = pio_add_program(pio, &ice_cram_program);

	return true;
}

static int pio_state_machine_init(void)
{
	// Try to fit the program into either PIO bank
	if (!pio_try_add_program(pio1)) {
		if (!pio_try_add_program(pio0)) {
				return -EIO;
		}
	}

	pio_sm_config c = ice_cram_program_get_default_config(offset);
	sm_config_set_out_pins(&c, hal_mosi, 1);
	sm_config_set_sideset_pins(&c, hal_clk);
	sm_config_set_clkdiv(&c, clk_div);
	sm_config_set_out_shift(&c, false, true, 8);
	pio_sm_init(pio, sm, offset, &c);

	pio_sm_set_enabled(pio, sm, true);

	pio_sm_set_consecutive_pindirs(pio, sm, hal_mosi, 1, true);
	pio_sm_set_consecutive_pindirs(pio, sm, hal_clk, 1, true);

	pio_gpio_init(pio, hal_mosi);
	pio_gpio_init(pio, hal_clk);

	return 0;
}

static void pio_state_machine_deinit(void)
{
	pio_sm_set_enabled(pio, sm, false);
	pio_sm_set_consecutive_pindirs(pio, sm, hal_mosi, 1, false);
	pio_sm_set_consecutive_pindirs(pio, sm, hal_clk, 1, false);
	pio_remove_program(pio, &ice_cram_program, offset);
	pio_sm_unclaim(pio, sm);
}

static int select_device(int mosi)
{
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < pi_spi_pins[i].mosi_len; j++) {
			if (pi_spi_pins[i].mosi[j] == mosi)
			{
				return i;
			}
		}
	}
	return -EINVAL;
}

static int check_miso(int miso, int dev)
{
	for (int j = 0; j < pi_spi_pins[dev].miso_len; j++) {
		if (pi_spi_pins[dev].miso[j] == miso)
		{
			return dev;
		}
	}
	return -EINVAL;
}

static int check_clk(int clk, int dev)
{
	for (int j = 0; j < pi_spi_pins[dev].clk_len; j++) {
		if (pi_spi_pins[dev].clk[j] == clk)
		{
			return dev;
		}
	}
	return -EINVAL;
}

int ICE_HAL_ATTR ice_hal_spi_init(int mosi, int miso, int clk, int freq)
{
	int dev;
	int ret;

	if (has_spi)
		return -1;

	dev = select_device(mosi);
	if (dev < 0) {
		/* check if we can apply inverse input/output PIO */
		dev = check_miso(mosi, 0);
		if (dev < 0) {
			dev = check_miso(mosi, 1);
			if (dev < 0)
				return dev;
		}
		is_pio = true;
	}


	if (check_clk(clk, dev) < 0)
			return -EINVAL;

	hal_miso = miso;
	hal_mosi = mosi;
	hal_clk = clk;

	if (is_pio) {
		ret = pio_state_machine_init();
		if (ret < 0)
			return ret;
	} else {

		if (miso >= 0) {
			if (check_miso(miso, dev) < 0)
				return -EINVAL;
		}

		ret = ice_hal_gpio_init(mosi);
		if (ret < 0)
			return ret;

		if (miso >= 0) {
			ret = ice_hal_gpio_init(miso);
			if (ret < 0)
				return ret;
		}

		ret = ice_hal_gpio_init(clk);
		if (ret < 0)
			return ret;

		ret = ice_hal_gpio_set_high_z(mosi);
		if (ret < 0)
			return ret;

		if (miso >= 0) {
			ret = ice_hal_gpio_set_high_z(miso);
			if (ret < 0)
				return ret;
		}

		ret = ice_hal_gpio_set_high_z(clk);
		if (ret < 0)
			return ret;

		if (dev == 0) {
			device = spi0;
		} else if (dev == 1) {
			device = spi1;
		} else {
			return -EINVAL;
		}

		spi_init(device, freq);
	}

	has_spi = true;

	return dev;
}

int ICE_HAL_ATTR ice_hal_spi_write(const uint8_t *buf, size_t len)
{
	int ret;

	if (!has_spi)
		return -EINVAL;

	if (is_pio) {
		for (int i = 0; i < len; ++i) {
			/* FIFO slots are 32-bits and the PIO state machine left shifts to get MSB first so need to
			 * pre-shift by 24 bits to get bit 7 of data byte into bit 31 of FIFO slot.
			 */
			pio_sm_put_blocking(pio, sm, buf[i] << 24);
		}
		    // Wait until the last byte has been pulled from the FIFO.
		while (!pio_sm_is_tx_fifo_empty(pio, sm)) {
			tight_loop_contents();
		}

		// At this point the last byte has been removed from the FIFO but the last bit might not have
		// been shifted out. Wait for the state machine to stall waiting for another bit
		// (which night never arrive).
		uint32_t mask = 1u << (sm + PIO_FDEBUG_TXSTALL_LSB);
		pio->fdebug = mask;
		while ((pio->fdebug & mask) == 0) {
			tight_loop_contents();
		}
	} else {
		gpio_set_function(hal_miso, GPIO_FUNC_SPI);
		gpio_set_function(hal_clk, GPIO_FUNC_SPI);
		gpio_set_function(hal_mosi, GPIO_FUNC_SPI);
		ret = spi_write_blocking(device, buf, len);
		ice_hal_gpio_set_high_z(hal_mosi);
		ice_hal_gpio_set_high_z(hal_clk);
		ice_hal_gpio_set_high_z(hal_miso);
		return ret;
	}

	return 0;
}

int ICE_HAL_ATTR ice_hal_spi_read(uint8_t *buf, int len)
{
	int ret;

	if (!has_spi)
		return -EINVAL;

	if (is_pio)
		return -ENOTSUP;

	gpio_set_function(hal_miso, GPIO_FUNC_SPI);
	gpio_set_function(hal_clk, GPIO_FUNC_SPI);
	gpio_set_function(hal_mosi, GPIO_FUNC_SPI);
	ret = spi_read_blocking(device, 0, buf, len);
	ice_hal_gpio_set_high_z(hal_mosi);
	ice_hal_gpio_set_high_z(hal_clk);
	ice_hal_gpio_set_high_z(hal_miso);
	return ret;
}

int ICE_HAL_ATTR ice_hal_spi_deinit(void)
{
	if (!has_spi)
		return -EINVAL;

	if (is_pio) {
		pio_state_machine_deinit();
	} else {
		spi_deinit(device);
	}

	has_spi = false;
	is_pio = false;

	return 0;
}

int ICE_HAL_ATTR ice_hal_gpio_init(int gpio)
{
	gpio_init(gpio);
	gpio_disable_pulls(gpio);
	gpio_put(gpio, false);
	/* set hiz */
	gpio_set_dir(gpio, GPIO_IN);
	return 0;
}

int ICE_HAL_ATTR ice_hal_gpio_set_high_z(int gpio)
{
	gpio_set_dir(gpio, GPIO_IN);
	gpio_disable_pulls(gpio);
	return 0;
}

int ICE_HAL_ATTR ice_hal_gpio_set_pu(int gpio)
{
	gpio_pull_up(gpio);
	return 0;
}

int ICE_HAL_ATTR ice_hal_gpio_set_pd(int gpio)
{
	gpio_pull_down(gpio);
	return 0;
}

int ICE_HAL_ATTR ice_hal_gpio_set_1(int gpio)
{
	gpio_put(gpio, true);
	gpio_set_dir(gpio, GPIO_OUT);
	return 0;
}

int ICE_HAL_ATTR ice_hal_gpio_set_0(int gpio)
{
	gpio_put(gpio, false);
	gpio_set_dir(gpio, GPIO_OUT);
	return 0;
}

int ICE_HAL_ATTR ice_hal_gpio_get(int gpio)
{
	return gpio_get(gpio) ? 1 : 0;
}

int ICE_HAL_ATTR ice_hal_gpio_deinit(int gpio)
{
	gpio_deinit(gpio);
	return 0;
}
