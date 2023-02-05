#ifndef ICE_FPGA_FLASH_H
#define ICE_FPGA_FLASH_H

#include <stdint.h>
#include <stddef.h>
#include "pico/stdlib.h"

#ifdef __cplusplus
extern "C" {
#endif

#define ICE_FLASH_PAGE_SIZE         256
#define ICE_FLASH_SECTOR_SIZE       4096

void ice_flash_init(void);
void ice_flash_deinit(void);
void static ice_flash_wait(void);
void ice_flash_read(uint32_t addr, uint8_t *buf, size_t sz);
void ice_flash_erase_sector(uint32_t addr);
void ice_flash_program_page(uint32_t addr, uint8_t const page[ICE_FLASH_PAGE_SIZE]);
void ice_flash_erase_chip(void);
void ice_flash_wakeup(void);
void ice_flash_sleep(void);
void ice_flash_enable_write(void);

#ifdef __cplusplus
}
#endif

#endif
