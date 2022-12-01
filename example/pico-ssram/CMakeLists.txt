cmake_minimum_required(VERSION 3.13)

# CMake configuration of pico-sdk
set(PICO_SDK_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../pico-sdk)
set(PICO_ICE_SDK_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../..)
set(PICO_BOARD pico_ice)
set(PICO_BOARD_HEADER_DIRS ${PICO_ICE_SDK_PATH}/include/boards)
include(${PICO_SDK_PATH}/pico_sdk_init.cmake)
project(pico_ice_hello_world)
pico_sdk_init()

# CMake configuration of the application
add_subdirectory(${PICO_ICE_SDK_PATH} pico-ice-sdk)
add_executable(firmware firmware.c)
target_link_libraries(firmware pico_ice_sdk pico_stdio_usb hardware_irq hardware_dma)

pico_add_extra_outputs(firmware)
