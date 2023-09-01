# pico_usb_spi

In addition to the main USB-CDC interface, used for the standard I/O (as used by `<stdio.h>`) (#0),
a second USB-CDC (#1) interface is created:

- mirrors all input from the USB-CDC to the SPI bus,
- mirrors back all SPI data to the USB-CDC

Use `/dev/ttyACM#` on Linux-like systems, and `COM#` on Windows system, replacing the `#` by the interface number, usually `2`.

```shell
python3 test.py /dev/ttyACM2
```
