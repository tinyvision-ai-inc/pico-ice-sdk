
if (NOT TARGET pico_ice_sdk)
    add_library(pico_ice_sdk INTERFACE)

    target_sources(pico_ice_sdk INTERFACE
        fpga_comm.c
        fpga.c
        flash.c
        fpga.c
        sdk.c
        smem.c
        tinyuf2/board_pico_ice.c
        tinyuf2/ghostfat.c
        tinyuf2/main.c
        tinyuf2/msc.c
        usb.c
        usb_descriptors.c
    )

    target_include_directories(pico_ice_sdk INTERFACE ../include)

    # This is in order to access the headers of the raspberrypi/pico-sdk, which
    # will add the -I flags.
    target_link_libraries(pico_ice_sdk INTERFACE
        tinyusb_device
        tinyusb_board
        pico_stdlib
        hardware_spi
        hardware_uart
        hardware_flash
        hardware_dma
    )
endif()
