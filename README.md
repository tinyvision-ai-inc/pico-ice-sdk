pico-ice-sdk
============

The firmware library for the [pico-ice](https://pico-ice.readthedocs.io/),
a board combining a Raspberry Pi RP2040 and an Lattice iCE40.

Before starting work with this repo, it is suggested that you read through the installation instructions for the Raspberry Pico processor [here](https://github.com/raspberrypi/pico-sdk). Specifically, you will need to install the ARM libraries using:

```
sudo apt install cmake gcc-arm-none-eabi libnewlib-arm-none-eabi libstdc++-arm-none-eabi-newlib
```

Also, its a good idea to set the `PICO_SDK_PATH` variable to the location of the local copy of the pico repo. If you dont do his, the process below will automaticaly download the repo for you.

To use this SDK, you do not need to download it, but only to drop the
`pico_ice_sdk_import.cmake` into your project, and add this Makefile:

```
cmake_minimum_required(VERSION 3.13)

## CMake configuration of pico-sdk and pico-ice-sdk
include(pico_ice_sdk_import.cmake)
project(pico_ice_firmware)
pico_sdk_init()

# CMake configuration of the application
add_executable(firmware firmware.c)
target_link_libraries(firmware pico_ice_sdk hardware_spi)
pico_add_extra_outputs(firmware)
```

This pico-ice-sdk and the Raspberry Pi pico-sdk will both be fetched
from git.

See the complete documentation at https://pico-ice.readthedocs.io/

See the project examples on the `examples` directory.


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
