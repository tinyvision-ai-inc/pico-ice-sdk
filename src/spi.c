#include "pico-ice.h"
#include "hardware/resets.h"
#include "hardware/regs/m0plus.h"
#include "hardware/structs/iobank0.h"
#include "hardware/structs/sio.h"
#include "hardware/structs/spi.h"
#include "hardware/structs/clocks.h"

static spi_fn_t *spi0_callback;
static spi_fn_t *spi1_callback;

void
spi_init(spi_hw_t *spi, uint8_t clock_divider, spi_fn_t *callback,
	uint8_t pin_sck, uint8_t pin_csn, uint8_t pin_rx, uint8_t pin_tx)
{
	uint32_t reset_bits = 0;
	int8_t irqn;

	/* register the callback */
	if (spi == spi0_hw)
		spi0_callback = callback;
	if (spi == spi1_hw)
		spi1_callback = callback;

	/* enable the peripheral clock, used by the TX/RX logic */
	clocks_hw->clk[clk_peri].ctrl = CLOCKS_CLK_PERI_CTRL_ENABLE_BITS;

	/* take I/O, and SPI out of reset */
        reset_bits |= 1 << 5;			/* iobank0 */
	reset_bits |= 1 << 8;			/* padsbank */
	reset_bits |= 1 << (16 + spi == spi0_hw ? 0 : 1);	/* spi0/spi1 */
	unreset_block_wait(reset_bits);

	/* setup the ports function, works for both any GPIO or SPI */
	iobank0_hw->io[pin_rx].ctrl = IO_BANK0_GPIO0_CTRL_FUNCSEL_VALUE_SPI0_RX;
	iobank0_hw->io[pin_csn].ctrl = IO_BANK0_GPIO1_CTRL_FUNCSEL_VALUE_SPI0_SS_N;
	iobank0_hw->io[pin_sck].ctrl = IO_BANK0_GPIO2_CTRL_FUNCSEL_VALUE_SPI0_SCLK;
	iobank0_hw->io[pin_tx].ctrl = IO_BANK0_GPIO3_CTRL_FUNCSEL_VALUE_SPI0_TX;

	/* set the direction of pins to input or output */
	sio_hw->gpio_oe_set = 1u << pin_sck | 1u << pin_csn | 1u << pin_tx;
	sio_hw->gpio_oe_clr = 1u << pin_rx;

	/* assume an incoming SSPCLK clock derived from clk_peri at 125MHz */
	spi->cr0 = 0
	/* propagate signals on positive edge (posege) */
	 | SPI_SSPCR0_SPH_BITS
	/* set the number of bits per frames */
	 | (8 - 1) << SPI_SSPCR0_DSS_LSB;

	/* the result of the division is expected to be >1 */
	assert(clock_divider >= 2 && clock_divider <= 254);
	clock_divider &= 0xFE;
	spi->cpsr = clock_divider;

	/* enable the SPI module *after* (#4.4.4) it was configured */
	spi->cr1 = SPI_SSPCR1_SSE_BITS;

	/* enable interrupts */
	irqn = (spi == spi0_hw ? 18 : 19);
	*(volatile uint32_t *)(PPB_BASE + M0PLUS_NVIC_ICPR_OFFSET) = 1u << irqn;
}

void
spi_start_io(spi_hw_t *spi)
{
	if (spi == spi0_hw)
		spi0_callback(spi0_hw, 0, (uint8_t *)&spi->dr);
	if (spi == spi1_hw)
		spi1_callback(spi1_hw, 0, (uint8_t *)&spi->dr);
	spi_enable_interrupts(spi);
}

void
__isr_spi0(void)
{
	/* on every byte, run the callback */
	if (spi0_hw->sr & SPI_SSPSR_TNF_BITS)
		/* let the programmer decide what to send in real-time */
		spi0_callback(spi0_hw, (uint8_t)spi0_hw->dr, (uint8_t *)&spi0_hw->dr);
}

void
__isr_spi1(void)
{
	/* on every byte, run the callback */
	if (spi1_hw->sr & SPI_SSPSR_TNF_BITS)
		/* let the programmer decide what to send in real-time */
		spi1_callback(spi1_hw, (uint8_t)spi1_hw->dr, (uint8_t *)&spi1_hw->dr);
}

void
spi_enable_interrupts(spi_hw_t *spi)
{
	spi->imsc = SPI_SSPIMSC_TXIM_BITS;
}

void
spi_disable_interrupts(spi_hw_t *spi)
{
	spi->imsc = 0x00;
}
