"empty" example
===============
This example is built as a CMake project:

```
mkdir -p build
cd build
cmake ..
make
```

This should produce a `firmware.uf2` file to flash onto the pico-ice RP2040 chip.
See the [main `README.md`](../../README.md) for how to do this.

It does nothing except providing the USB features: flashing a bitfile, forwarding the FPGA UART over USB-UART #1
