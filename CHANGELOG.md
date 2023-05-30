# Changelog

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
