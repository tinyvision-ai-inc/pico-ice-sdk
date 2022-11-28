"template" example
==================
This example is built as a CMake project:

```
mkdir -p examples/pico-template/build
cd examples/pico-template/build
cmake ..
make
```

This should produce a `firmware.uf2` file to flash onto the pico-ice RP2040 chip.

It is purposely not doing anything but the base USB features: the two UART interfaces
(one for the Pico, one for the iCE40) and the storage device (for uploading the FPGA
bitstream).
