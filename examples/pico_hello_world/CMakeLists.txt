cmake_minimum_required(VERSION 3.13)

set(PICO_SDK_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../pico-sdk)
include(pico_sdk_import.cmake)

project(pico_hello_world C CXX ASM)

pico_sdk_init()

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../.. pico-ice-sdk)

add_executable(pico_hello_world
    main.c
    usb_descriptors.c
)
target_link_libraries(pico_hello_world
    pico_ice_sdk
    pico_ice_usb
    pico_stdio_usb
)
target_include_directories(pico_hello_world PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)
pico_enable_stdio_usb(pico_hello_world 1)
pico_enable_stdio_uart(pico_hello_world 0)
pico_add_extra_outputs(pico_hello_world)
