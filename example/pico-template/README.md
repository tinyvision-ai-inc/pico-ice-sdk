Project template
================
This example content is meant to be copied into your own git repository, along with two git submodules:
From a new

```sh
# create a new repository
git init your-project
cd your-project

# add the dependencies as submodules
git submodule add https://github.com/tinyvision-ai-inc/pico-ice-sdk
git submodule add https://github.com/raspberrypi/pico-sdk
git -C pico-sdk submodule update --recursive

# import this empty project template
cp -r pico-ice-sdk/example/pico-template/* .
```

You can then build your own project as a normal CMake project:

```
mkdir -p build
cd build
cmake ..
make
```

This should produce a `firmware.uf2` file to flash onto the pico-ice RP2040 chip.
See the [main `README.md`](../../README.md) for how to do this.

It will also have all the USB features enabled (flashing a bitfile, forwarding the FPGA UART over USB-UART #1)
as long as `tud_task()` is called repeatedly.
