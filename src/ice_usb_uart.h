//
// Created by MrJake222 on 03/11/24.
//

#pragma once
#include "tusb.h"
#include "tusb_config.h"

#define ICE_USB_UART_RBBITS 12
#define ICE_USB_UART_RBSIZE (1<<ICE_USB_UART_RBBITS)

void ice_usb_uart_init();
void ice_usb_uart_task();

// callback functions
// auto-decide whether the itf number is bound to UART or not
// call always, without if/ifdef, return 1 if handled (stop other processing)
int ice_usb_uart_cb_baud(int itf, unsigned int baud);
int ice_usb_uart_cb_rx(int itf);