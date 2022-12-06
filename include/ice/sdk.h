/** Global SDK actions.
* Initialize the board, including USB, but ice_usb_task() should still be called in the main loop.
* \defgroup sdk
*/

#ifndef _ICE_SDK_H
#define _ICE_SDK_H

#include <stdint.h>
#include <assert.h>
#include "bsp/board.h"

void ice_sdk_init(void);

#endif
