/** Initialize the board, including USB, but ice_usb_task() should still be called in the main loop.
* \defgroup init
*/

#ifndef ICE_INIT_H
#define ICE_INIT_H

#include <stdint.h>
#include <assert.h>
#include "bsp/board.h"

void ice_init_sdk(void);

#endif
