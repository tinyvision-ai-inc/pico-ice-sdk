# pico_usb_fpga

In addition to the main USB-UART interface, used for the standard I/O (as used by `<stdio.h>`) (#0),
a second USB-UART (#1) interface is created:

- Accept
  [wishbone-serial](https://wishbone-utils.readthedocs.io/en/latest/wishbone-tool/#serial-bridge)
  requests from USB CDC.
- Mirrors all requests over
  [wishbone-spi](https://wishbone-utils.readthedocs.io/en/latest/wishbone-tool/#spi-bridge)
  to the FPGA over SPI.

Any shared I/O pins can be used. In this example, pins 0 and 1 are used.
