# pico-ice-sdk

This is a library for using the [pico-ice](https://pico-ice.tinyvision.ai/),
a board combining a Raspberry Pi RP2040 and an Lattice iCE40.

You will need an ARM compiler toolchain (see [pico-sdk](https://github.com/raspberrypi/pico-sdk)):

```
sudo apt install cmake gcc-arm-none-eabi libnewlib-arm-none-eabi libstdc++-arm-none-eabi-newlib
```

You can copy-paste [`pico-template`](example/pico-template) and add this directory as a submodule to get started.

Make sure to update all submodules before trying the [examples](example):

```
git submodule update --init
git -C pico-sdk submodule update --init
```

See the [doc]()
