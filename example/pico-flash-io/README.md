"flash-io" example
==================
This example is built as a CMake project:

```
mkdir -p build
cd build
cmake ..
make
```

This should produce a `pico_flash_io.uf2` file to flash onto the pico-ice RP2040 chip.
See the [main `README.md`](../../README.md) for how to do this.

It will program a register of the flash chip, read it back, and dump its content over USB-UART #0.

It will also have all the USB features enabled (flashing a bitfile, forwarding the FPGA UART over USB-UART #1).
