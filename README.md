pico-ice-sdk
============

The firmware library for the [pico-ice](https://pico-ice.readthedocs.io/),
a board combining a Raspberry Pi RP2040 and an Lattice iCE40.

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
