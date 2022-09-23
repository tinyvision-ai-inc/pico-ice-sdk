#ifndef PICO_ICE_PRIV_H
#define PICO_ICE_PRIV_H

/*
 * All functions defined for internal use, not useful for using the SDK.
 */

// in src/usb_cdc.c
void tud_task_cdc(void);

// in src/tinyuf2/uf2.h
void uf2_init(void);

#endif
