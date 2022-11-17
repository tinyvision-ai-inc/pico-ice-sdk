"hello world" example
=====================
This example is built as a CMake project:

```
mkdir -p examples/pico-template/build
cd examples/pico-template/build
cmake ..
make
```

This should produce a `firmware.uf2` file to flash onto the pico-ice RP2040 chip.

See the [main `README.md`](../../README.md) for how to do this.

This demo prints "hello world" continuously through the USB UART interface.

After flashing the firmware and unmounting the drive, it will reboot and the USB
interface will show-up two UARTs (one for the Pico, one for the iCE40) and one storage
device (for uploading the FPGA bitstream).

The first UART will be printing "hello world".
