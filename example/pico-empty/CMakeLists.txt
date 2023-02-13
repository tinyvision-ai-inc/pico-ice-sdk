cmake_minimum_required(VERSION 3.13)

set(PICO_SDK_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../pico-sdk)
set(PICO_ICE_SDK_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../..)
set(PICO_BOARD pico_ice)
set(PICO_BOARD_HEADER_DIRS ${PICO_ICE_SDK_PATH}/include/boards)

include(${PICO_SDK_PATH}/pico_sdk_init.cmake)

project(pico-empty C CXX ASM)

pico_sdk_init()

add_subdirectory(${PICO_ICE_SDK_PATH}/src pico-ice-sdk)

add_executable(pico_empty
    firmware.c
    usb_descriptors.c
)

target_include_directories(pico_empty PUBLIC
    .
)

target_link_libraries(pico_empty
    pico_ice_sdk
    pico_ice_usb
    pico_stdio_usb
)

pico_add_extra_outputs(pico_empty)
