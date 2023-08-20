# pico_usb_spi

In addition to the main USB-CDC interface, used for the standard I/O (as used by `<stdio.h>`) (#0),
a second USB-CDC (#1) interface is created:

- mirrors all input from the USB-CDC to the SPI bus,
- mirrors back all SPI data to the USB-CDC
