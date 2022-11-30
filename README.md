pico-ice-sdk
============

This is the firmware library for the [pico-ice](https://pico-ice.readthedocs.io/),
a board combining a Raspberry Pi RP2040 and an Lattice iCE40.

You will need an ARM development environment as described by the [pico-sdk](https://github.com/raspberrypi/pico-sdk):

```
sudo apt install cmake gcc-arm-none-eabi libnewlib-arm-none-eabi libstdc++-arm-none-eabi-newlib
```

See the [`pico-template`](example/pico-template) to setup this SDK into your project.

Make sure to update all submodules before trying the [examples](example):

```
git submodule update --init
git -C pico-sdk submodule update --init
```

Flash a RP2040 firmware image
-----------------------------
To upload a _new_ firmware image on the PR2040 (the "pico" part of "pico-ice"):

**Step 1:** Connect the `USB_BOOT` pin to ground.

**Step 2:** Press and release the "RESET" button.

**Step 3:** Disconnect the `USB_BOOT` pin from ground.

**Step 4:** Look for an USB drive and mount it, open it, and check that there are only 2 files in it: `INFO.HTML` and `INFO_UF2.TXT`.
If you also have an `CURRENT.UF2`, this means you found the FPGA flashing interface, and need to retry steps 1, 2, 3.

**Step 5:** Copy the `firmware.uf2` file you just built onto the USB drive.

**Step 6:** Eject the memory drive.

At this step, the firmware should be uploaded. Shorting the `USB_BOOT` pin to ground is necessary only to boot the pico into the default bootloader.
