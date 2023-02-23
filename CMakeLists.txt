cmake_minimum_required(VERSION 3.13)

# board declaration

if (NOT DEFINED PICO_BOARD)
    set(PICO_BOARD pico_ice)
endif()
list(APPEND PICO_BOARD_HEADER_DIRS "${CMAKE_CURRENT_LIST_DIR}/include/boards")

# main library with the whole pico-ice-sdk

add_library(pico_ice_sdk INTERFACE)
target_sources(pico_ice_sdk INTERFACE
    src/ice_fpga.c
    src/ice_spi.c
    src/ice_flash.c
    src/ice_led.c
    src/ice_cram.c
    src/ice_usb.c
)
target_include_directories(pico_ice_sdk INTERFACE
    include
)
target_link_libraries(pico_ice_sdk INTERFACE
    hardware_flash
    hardware_gpio
    hardware_pio
    hardware_spi
    hardware_uart
    pico_stdlib
    pico_unique_id
)
pico_generate_pio_header(pico_ice_sdk
    ${CMAKE_CURRENT_LIST_DIR}/src/ice_cram.pio
)

# second library with just tinyuf2

add_library(tinyuf2 INTERFACE)
target_sources(tinyuf2 INTERFACE
    src/tinyuf2/board_pico_ice.c
    src/tinyuf2/ghostfat.c
    src/tinyuf2/main.c
    src/tinyuf2/msc.c
)
target_include_directories(pico_ice_sdk INTERFACE
    include
    src
)
