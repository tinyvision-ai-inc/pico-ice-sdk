
if (NOT TARGET pico_ice_sdk)
    add_library(pico_ice_core INTERFACE)

    target_sources(pico_ice_core INTERFACE
        ice_fpga.c
        ice_fpga_comm.c
        ice_fpga_flash.c
        ice_smem.c
    )

    target_include_directories(pico_ice_core INTERFACE ../include)

    # This is in order to access the headers of the raspberrypi/pico-sdk, which
    # will add the -I flags.
    target_link_libraries(pico_ice_core INTERFACE
        hardware_gpio
        hardware_spi
        hardware_uart
        hardware_dma
    )

    add_library(pico_ice_usb INTERFACE)

    target_sources(pico_ice_usb INTERFACE
        tinyuf2/board_pico_ice.c
        tinyuf2/ghostfat.c
        tinyuf2/main.c
        tinyuf2/msc.c
        usb_descriptors.c
    )

    target_compile_definitions(pico_ice_usb INTERFACE CFG_TUSB_CONFIG_FILE="pico_ice_tusb_config.h")

    target_sources(pico_ice_usb INTERFACE
        ice_usb.c
    )

    target_include_directories(pico_ice_usb INTERFACE ../include)

    target_link_libraries(pico_ice_usb INTERFACE
        hardware_flash
        tinyusb_device
        tinyusb_board
        pico_stdlib
    )


    add_library(pico_ice_sdk INTERFACE)

    target_sources(pico_ice_sdk INTERFACE
        ice_sdk.c
    )

    target_link_libraries(pico_ice_sdk INTERFACE
        pico_ice_core
        pico_ice_usb
        pico_stdlib
    )

endif()
