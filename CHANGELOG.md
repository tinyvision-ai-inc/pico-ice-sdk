# Changelog

## v1.5.0

* In the USB DFU interface, swap the alt=0 and alt=1 numbers to get APIO and
  IceStudio to work again out of the box.

* Fix DFU CRAM programming.

## v1.3.1

* Make USB enumerate better in MacOS and everywhere (@dicristina).

## v1.3.0

* Switch SPI to hardware back-end with DMA (@MichaelBell).
  This applies to all code as `<ice_spi.h>` is used everywhere.

* Introduce ICE_USB_SPI_CDC: a new USB protocol to access the various SPI
  parts, along with a new host-side python library for it.

## v1.2.1

* With the default firmware, the FPGA was rebooting after a few seconds due
  to the operating system reading the USB interface. We now let the FPGA run
  even when that happens, and only reset it on write calls.

## v1.2.0

* Fix UART forwarding in the SDK while used in combination with the TinyUF2
  firmware, which resurfced again.

* Offer a reduced API for configuring forwarding of UART among other things.
  Improved documentation in parallel.

## v1.1.2

* Fix TinyUF2 stopping the FPGA while being read, which happens at every boot
  with the operating system peeking at the various files in the USB drive out
  of curiosity.

* Fix UART forwarding in the SDK while used in combination with the TinyUF2
  firmware, which takes over the default UART for logging.

## v1.1.1

* Fix UART forwarding in the SDK and example.

## v1.1.0

* Fix TinyUF2 on Windows
* Easier USB configuration only requiring to change `tusb_config.h`.

## v1.0.0

* Libraries to communicate with each chip of the device
* All exapmles working except pico_fpga_io and pico_usb_keyboard

## v0.1.0

* (fix) PIO-based CRAM programming works again
* The bit-banged SPI library does not need any `tx_rx_swapp` parameter anymore.

## v0.0.0

* (new) USB configuration works,
* (new) bit-banged ice_spi.h that can swap TX/RX and API ready for DMA (not DMA support yet),
* DFU to iCE40 external flash works,
* LEDs control works,
* Everything else does not work yet
