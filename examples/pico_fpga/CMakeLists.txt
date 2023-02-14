cmake_minimum_required(VERSION 3.13)

set(PICO_SDK_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../pico-sdk)
include(pico_sdk_import.cmake)

project(my_firmware C CXX ASM)

pico_sdk_init()

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../.. pico-ice-sdk)
pico_add_extra_outputs(my_firmware)

add_executable(firmware
    main.c
)

target_link_libraries(firmware
    pico_ice_sdk
    pico_stdio_usb
)

