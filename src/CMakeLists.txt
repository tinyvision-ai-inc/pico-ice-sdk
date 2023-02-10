add_library(pico_ice_sdk INTERFACE)
target_sources(pico_ice_sdk INTERFACE
    ice_fpga.c
    ice_spi.c
    ice_flash.c
    ice_led.c
)
target_include_directories(pico_ice_sdk INTERFACE
    ../include
)
target_link_libraries(pico_ice_sdk INTERFACE
    hardware_flash
    hardware_gpio
    hardware_spi
    hardware_uart
    pico_stdlib
    pico_unique_id
)

add_library(pico_ice_usb INTERFACE)
target_sources(pico_ice_sdk INTERFACE
    ice_usb.c
)
target_include_directories(pico_ice_sdk INTERFACE
    ../include
)
target_link_libraries(pico_ice_usb INTERFACE
    tinyusb_board
    tinyusb_device
)

add_library(tinyuf2 INTERFACE)
target_sources(tinyuf2 INTERFACE
    tinyuf2/board_pico_ice.c
    tinyuf2/ghostfat.c
    tinyuf2/main.c
    tinyuf2/msc.c
)
target_include_directories(pico_ice_usb INTERFACE
    .
)
target_link_libraries(pico_ice_usb INTERFACE
    tinyusb_board
    tinyusb_device
)
