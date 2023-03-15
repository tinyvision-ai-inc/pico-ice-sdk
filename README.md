# pico-ice-sdk

[doc](https://pico-ice.tinyvision.ai/) -
[pcb](https://github.com/tinyvision-ai-inc/pico-ice) -
![status](https://github.com/tinyvision-ai-inc/pico-ice-sdk/actions/workflows/main.yml/badge.svg)

This is a library for using the [pico-ice](https://pico-ice.tinyvision.ai/),
a board combining a Raspberry Pi RP2040 and an Lattice iCE40.

You will need an ARM compiler toolchain (see [pico-sdk](https://github.com/raspberrypi/pico-sdk)):

```sh
sudo apt install cmake gcc-arm-none-eabi libnewlib-arm-none-eabi libstdc++-arm-none-eabi-newlib
```

## Template

To start with a new project, you can copy the <template/> directory:

```sh
cp -r template ~/my-project
cd ~/my-project
git init .
git submodule add https://github.com/raspberrypi/pico-sdk/
git submodule add https://github.com/tinyvision-ai-inc/pico-ice-sdk/
git -C pico-sdk submodule update --init lib/tinyusb
```

Then build it like a normal CMake project and upload the `my_firmware.uf2` as described in:
<https://datasheets.raspberrypi.com/pico/getting-started-with-pico.pdf>

```sh
mkdir build
cd build
cmake ..
make
```

## Examples

The examples can be built immediately in this repository.
You will first need to init the `pico-ice` submodule:

```
git submodule update --init
git -C pico-sdk submodule update --init lib/tinyusb
```

And then build all the examples together:

```
mkdir -p examples/build
cd examples/build
cmake ..
make
```

This should produce one `.uf2` per example, able to be flashed onto the pico-ice RP2040 chip.
