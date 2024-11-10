//
// Copyright (c) 2024 MrJake222
// SPDX-License-Identifier: MIT
//

#pragma once
#include "tusb.h"
#include "tusb_config.h"

void ice_usb_uart_init();
void ice_usb_uart_task();

// callback functions
int ice_usb_uart_cb_coding(int itf, uint baud, int stop_bits, int parity, int data_bits);