"pico-usb-keyboard" example
================
This example is built as a CMake project:

```
mkdir -p build
cd build
cmake ..
make
```

This should produce a `pico_usb_keyboard.uf2` file to flash onto the pico-ice RP2040 chip.
See the [main `README.md`](../../README.md) for how to do this.

Connect a USB keyboard and an external 5V power supply to VDC. The LED should blink whenever
you press a key. The pattern blinked by the LED is the HID key code.
