cmake_minimum_required(VERSION 3.13)

execute_process(COMMAND git -C "${CMAKE_CURRENT_LIST_DIR}" describe --tags
    OUTPUT_VARIABLE PICO_ICE_SDK_VERSION
    OUTPUT_STRIP_TRAILING_WHITESPACE
    )
set(PICO_ICE_SDK_VERSION ${PICO_ICE_SDK_VERSION} PARENT_SCOPE)

add_library(pico_ice_sdk INTERFACE)

target_sources(pico_ice_sdk INTERFACE
    src/ice_fpga.c
    src/ice_flash.c
    src/ice_led.c
    src/ice_cram.c
    src/ice_fpga_data.c
    src/pico-sdk_ice_hal.c
    )
target_include_directories(pico_ice_sdk INTERFACE
    include
    )
target_link_libraries(pico_ice_sdk INTERFACE
    pico_ice_preinit_common
    hardware_flash
    hardware_gpio
    hardware_pio
    hardware_spi
    hardware_dma
    hardware_uart
    pico_stdlib
    )
pico_generate_pio_header(pico_ice_sdk
    ${CMAKE_CURRENT_LIST_DIR}/src/ice_cram.pio
    )
target_include_directories(pico_ice_sdk INTERFACE
    include
    )

add_library(pico_ice_usb INTERFACE)

target_sources(pico_ice_usb INTERFACE
    src/ice_usb.c
    src/tinyuf2_main.c
    src/tinyuf2_board.c
    src/tinyuf2_include.c
    )
target_include_directories(pico_ice_usb INTERFACE
    include
    lib/tinyuf2/src
    )
target_link_libraries(pico_ice_usb INTERFACE
    pico_ice_preinit_common
    pico_multicore
    pico_unique_id
    tinyusb_device
    tinyusb_board
    )
