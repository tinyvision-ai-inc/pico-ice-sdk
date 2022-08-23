#ifndef PICO_ICE_H
#define PICO_ICE_H

extern void gpio_init(void);
extern void gpio_set_mode_output(uint8_t pin);
extern void gpio_set_pin_value(uint8_t pin, bool value);

#endif
