cmake_minimum_required(VERSION 3.13)

set(PICO_SDK_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../pico-sdk)
include(pico_sdk_import.cmake)

project(pico_blinky C CXX ASM)

pico_sdk_init()

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../.. pico-ice-sdk)

add_executable(pico_blinky
    main.c
)
target_link_libraries(pico_blinky
    pico_ice_sdk
)
pico_add_extra_outputs(pico_blinky)
