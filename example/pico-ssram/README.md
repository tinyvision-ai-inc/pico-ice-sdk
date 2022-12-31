SSRAM DMA example
=================
This example shows you how to use a DMA to write and read the SPI SSRAM on the board. It uses an instance of the SPI to do this.

This example is built as a CMake project:
```
cd example/pico-ssram
mkdir -p build
cd build
cmake ..
make
```

This should produce a `pico_ssram.uf2` file to flash onto the pico-ice RP2040 chip.
See the [main `README.md`](../../README.md) for how to do this.

It will also have all the USB features enabled (flashing a bitfile, forwarding the FPGA UART over USB-UART #1)
as long as `ice_usb_task()` is called repeatedly.
