cmake_minimum_required(VERSION 3.13)

# CMake configuration of pico-sdk
set(PICO_SDK_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../pico-sdk)
set(PICO_ICE_SDK_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../..)
set(PICO_BOARD pico_ice)
set(PICO_BOARD_HEADER_DIRS ${PICO_ICE_SDK_PATH}/include/boards)
include(${PICO_SDK_PATH}/pico_sdk_init.cmake)
project(pico-hello-world C CXX ASM)
pico_sdk_init()

# CMake configuration of the application
add_subdirectory(${PICO_ICE_SDK_PATH}/src pico-ice-sdk)
add_executable(pico_hello_world firmware.c)
target_link_libraries(pico_hello_world pico_ice_sdk)
pico_enable_stdio_usb(pico_hello_world 1)
pico_add_extra_outputs(pico_hello_world)
