#include "pico.h"
#include "hardware/structs/spi.h"

#ifndef PICO_ICE_H
#define PICO_ICE_H

/* GPIO */

extern void gpio_init(void);
extern void gpio_set_mode_output(uint8_t pin);
extern void gpio_set_pin_value(uint8_t pin, bool value);

/* SPI */

/* interrupt handler for SPI events */
typedef void spi_fn_t(spi_hw_t *spi, uint8_t rx, uint8_t volatile *tx);

/* run the callback registered by spi_init() */
extern void __isr_spi0(void);
extern void __isr_spi1(void);

/* the clock speed might not be exact due to integer division */
extern void spi_init(spi_hw_t *spi, uint8_t clock_divider, spi_fn_t *callback,
	uint8_t pin_sck, uint8_t pin_csn, uint8_t pin_rx, uint8_t pin_tx);

/* start the I/O on an SPI device, with the first rx 0x0 */
extern void spi_start_io(spi_hw_t *spi);

/* set SPI interrupts on or off */
extern void spi_enable_interrupts(spi_hw_t *spi);
extern void spi_disable_interrupts(spi_hw_t *spi);

#endif
