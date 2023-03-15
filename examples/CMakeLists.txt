cmake_minimum_required(VERSION 3.13)

set(PICO_SDK_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../lib/pico-sdk)
include(pico_sdk_import.cmake)

project(pico_ice_examples C CXX ASM)

pico_sdk_init()

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/.. pico-ice-sdk)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/pico_blinky)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/pico_blinky_cplusplus)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/pico_cram)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/pico_flash_io)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/pico_flash_repl)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/pico_fpga)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/pico_fpga_io)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/pico_hello_world)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/pico_usb_keyboard)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/pico_usb_uart)

# To be updated and debugged
#add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/pico_ssram)
