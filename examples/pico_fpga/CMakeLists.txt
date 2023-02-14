cmake_minimum_required(VERSION 3.13)

set(PICO_SDK_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../pico-sdk)
include(pico_sdk_import.cmake)

project(pico_fpga C CXX ASM)

pico_sdk_init()

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../.. pico-ice-sdk)

add_executable(pico_fpga
    main.c
    usb_descriptors.c
)
target_link_libraries(pico_fpga
    pico_ice_sdk
    pico_ice_usb
    pico_stdio_usb
)
target_include_directories(pico_fpga PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)
pico_enable_stdio_usb(pico_fpga 1)
pico_enable_stdio_uart(pico_fpga 0)
pico_add_extra_outputs(pico_fpga)
