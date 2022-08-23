#include <stdbool.h>
#include "pico-ice.h"
#include "hardware/resets.h"
#include "hardware/structs/sio.h"
#include "hardware/regs/io_bank0.h"
#include "hardware/structs/iobank0.h"

void
gpio_init(void)
{
	unreset_block_wait(1 << 5 /* IO_BANK0 */ | 1 << 8 /* Pads - bank */);
}

void
gpio_set_mode_output(uint8_t pin)
{
	sio_hw->gpio_oe_set = 1u << pin;
	iobank0_hw->io[pin].ctrl = IO_BANK0_GPIO0_CTRL_FUNCSEL_VALUE_SIO_0;
}

void
gpio_set_pin_value(uint8_t pin, bool val)
{
	sio_hw->gpio_set = val << pin;
}
