cmake_minimum_required(VERSION 3.13)

set(PICO_SDK_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../pico-sdk)
include(pico_sdk_import.cmake)

project(pico_flash_io C CXX ASM)

pico_sdk_init()

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../.. pico-ice-sdk)

add_executable(pico_flash_io
    main.c
    usb_descriptors.c
)
target_link_libraries(pico_flash_io
    pico_ice_sdk
    pico_ice_usb
)
target_include_directories(pico_flash_io PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)
pico_add_extra_outputs(pico_flash_io)
