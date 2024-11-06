cmake_minimum_required(VERSION 3.12)

set(PICO_SDK_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../lib/pico-sdk)
include(${PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(pico_ice_examples C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
pico_sdk_init()

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/pico-ice-sdk)

add_subdirectory(pico_blinky)
add_subdirectory(pico_blinky_cplusplus)
add_subdirectory(pico_cram)
# colides with pico sdk target
#add_subdirectory(pico_flash)
add_subdirectory(pico_flash_repl)
add_subdirectory(pico_fpga)
add_subdirectory(pico_fpga_io)
add_subdirectory(pico_hello_world)
# doesn't build
#add_subdirectory(pico_ice_blinky)
add_subdirectory(pico_sram)
add_subdirectory(pico_usb_fpga)
add_subdirectory(pico_usb_keyboard)
add_subdirectory(pico_usb_spi)
add_subdirectory(pico_usb_uart)
add_subdirectory(pico_usb_uf2)
