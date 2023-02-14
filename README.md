# pico-ice-sdk

[doc](https://pico-ice.tinyvision.ai/) - [pcb](https://github.com/tinyvision-ai-inc/pico-ice)

This is a library for using the [pico-ice](https://pico-ice.tinyvision.ai/),
a board combining a Raspberry Pi RP2040 and an Lattice iCE40.

You will need an ARM compiler toolchain (see [pico-sdk](https://github.com/raspberrypi/pico-sdk)):

```sh
sudo apt install cmake gcc-arm-none-eabi libnewlib-arm-none-eabi libstdc++-arm-none-eabi-newlib
```

## Quickstart

To start with a new project, you can copy the <template/> directory:

```sh
cp -r template ~/my_firmware
cd ~/my_firmware
git init .
git submodule add https://github.com/raspberrypi/pico-sdk/
git submodule add https://github.com/tinyvision-ai-inc/pico-ice-sdk/
git -C pico-sdk submodule update --init lib/tinyusb
```

Then build it like a normal CMake project and upload the `my_firmware.uf2` as described in:
<https://datasheets.raspberrypi.com/pico/getting-started-with-pico.pdf>

## Examples

The examples can be built immediately in this repository.
You will first need to init the `pico-ice` submodule:

```
git submodule update --init
git -C pico-sdk submodule update --init lib/tinyusb
```

And the build any of the example as a normal CMake project:

```
cd pico_example_dir
mkdir -p build
cd build
cmake ..
make
```

This should produce a `.uf2` file to flash onto the pico-ice RP2040 chip.
