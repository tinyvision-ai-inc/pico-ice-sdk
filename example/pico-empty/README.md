"empty" example
===============
This example is built as a CMake project:

```
mkdir -p build
cd build
cmake ..
make
```

This should produce a `pico_empty.uf2` file to flash onto the pico-ice RP2040 chip.
See the [main `README.md`](../../README.md) for how to do this.

It does nothing except USB DFU and letting the FPGA start.
