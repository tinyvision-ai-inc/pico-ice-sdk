cmake_minimum_required(VERSION 3.13)

## CMake configuration of pico-sdk and pico-ice-sdk
include(pico_ice_sdk_import.cmake)
project(pico_ice_firmware)
pico_sdk_init()

# CMake configuration of the application
add_executable(firmware firmware.c)
target_link_libraries(firmware pico_ice_sdk pico_stdio_usb)
pico_add_extra_outputs(firmware)
