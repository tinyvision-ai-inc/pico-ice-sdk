cmake_minimum_required(VERSION 3.13)

# CMake configuration of pico-sdk
set(PICO_SDK_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../pico-sdk)
set(PICO_ICE_SDK_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../..)
set(PICO_BOARD pico_ice)
set(PICO_BOARD_HEADER_DIRS ${PICO_ICE_SDK_PATH}/include/boards)
include(${PICO_SDK_PATH}/pico_sdk_init.cmake)
project(pico-usb-keyboard C CXX ASM)
pico_sdk_init()

# CMake configuration of the application
add_subdirectory(${PICO_ICE_SDK_PATH}/src pico-ice-sdk)
add_executable(pico_usb_keyboard firmware.c)

# As a USB host, USB stdio is not possible.
pico_enable_stdio_usb(pico_usb_keyboard 0)

# Make sure TinyUSB can find target specific tusb_config.h
target_include_directories(pico_usb_keyboard PUBLIC ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(pico_usb_keyboard
    pico_ice_core
    pico_stdlib
    tinyusb_board
    tinyusb_host
)

pico_add_extra_outputs(pico_usb_keyboard)
