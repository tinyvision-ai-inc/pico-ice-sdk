#ifndef ICE_INIT_H
#define ICE_INIT_H
/**
 * Initialize the board, including USB, but ice_usb_task() should still be called in the main loop.
 * @defgroup init
 * @{
 */
#include <stdint.h>
#include <assert.h>
#include "boards/pico_ice.h"
#include "bsp/board.h"

void ice_init(void);

/** @} */
#endif
