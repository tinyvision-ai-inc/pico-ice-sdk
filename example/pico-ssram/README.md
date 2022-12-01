SSRAM DMA example
================
This example shows you how to use a DMA to write and read the SPI SSRAM on the board. It uses an instance of the SPI to do this.
Thanks to z80 for most of the code in this example.

Repo setup
==========

```sh
# create a new repository
git init your-project
cd your-project

# add the dependencies as submodules
git submodule add https://github.com/tinyvision-ai-inc/pico-ice-sdk
git submodule add https://github.com/raspberrypi/pico-sdk
git -C pico-sdk submodule update --recursive
```

Now we build the SSRAM
```
cd example/pico-ssram
mkdir -p build
cd build
cmake ..
make
```

This should produce a `firmware.uf2` file to flash onto the pico-ice RP2040 chip.
See the [main `README.md`](../../README.md) for how to do this.

It will also have all the USB features enabled (flashing a bitfile, forwarding the FPGA UART over USB-UART #1)
as long as `ice_usb_task()` is called repeatedly.
