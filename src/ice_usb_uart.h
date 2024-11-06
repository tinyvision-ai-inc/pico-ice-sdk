//
// Created by MrJake222 on 03/11/24.
//

#pragma once
#include "tusb.h"
#include "tusb_config.h"

void ice_usb_uart_init();
void ice_usb_uart_task();

// callback functions
int ice_usb_uart_cb_baud(int itf, unsigned int baud);