#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

void ice_cram_open(void);
void ice_cram_write(const uint8_t *buf, size_t len);
bool ice_cram_close(void);

#ifdef __cplusplus
}
#endif
