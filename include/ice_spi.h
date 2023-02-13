#pragma once
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

void ice_spi_init(void);
void ice_spi_chip_select(uint8_t csn_pin);
void ice_spi_chip_deselect(uint8_t csn_pin);
void ice_spi_write_async(uint8_t const *buf_w, size_t len, void (*callback)(volatile void *), void *context);
void ice_spi_read_async(uint8_t tx, uint8_t *buf_r, size_t len, void (*callback)(volatile void *), void *context);
bool ice_spi_is_async_complete(void);
void ice_spi_await_async_completion(void);
void ice_spi_read_blocking(uint8_t tx, uint8_t *buf, size_t len);
void ice_spi_write_blocking(uint8_t const *buf, size_t len);
