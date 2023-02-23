cmake_minimum_required(VERSION 3.13)

set(PICO_SDK_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../pico-sdk)
include(pico_sdk_import.cmake)

project(pico_usb_uart C CXX ASM)

pico_sdk_init()

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../.. pico-ice-sdk)

add_executable(pico_usb_uart
    main.c
    usb_descriptors.c
)
target_link_libraries(pico_usb_uart
    pico_ice_sdk
    tinyusb_device
)
target_include_directories(pico_usb_uart PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)
pico_add_extra_outputs(pico_usb_uart)
