
if (NOT TARGET pico_ice_sdk)
    #### pico_ice_fpga ####
    
    add_library(pico_ice_fpga INTERFACE)
    target_sources(pico_ice_fpga INTERFACE
        ice_fpga.c
        ice_fpga_comm.c
        ice_fpga_flash.c
    )
    target_include_directories(pico_ice_fpga INTERFACE ../include)
    target_link_libraries(pico_ice_fpga INTERFACE
        hardware_flash
        hardware_gpio
        hardware_irq
        hardware_spi
        hardware_dma
    )

    #### pico_ice_smem ####
    
    add_library(pico_ice_smem INTERFACE)
    target_sources(pico_ice_smem INTERFACE
        ice_smem.c
    )
    target_include_directories(pico_ice_smem INTERFACE ../include)
    target_link_libraries(pico_ice_smem INTERFACE
        hardware_gpio
        hardware_irq
        hardware_spi
        hardware_dma
        hardware_sync
    )

    #### pico_ice_usb ####
    
    add_library(pico_ice_usb INTERFACE)
    target_sources(pico_ice_usb INTERFACE
        ice_usb.c
        tinyuf2/board_pico_ice.c
        tinyuf2/ghostfat.c
        tinyuf2/main.c
        tinyuf2/msc.c
        usb_descriptors.c
    )
    target_include_directories(pico_ice_usb INTERFACE ../include)
    target_link_libraries(pico_ice_usb INTERFACE
        hardware_uart
        tinyusb_device
        tinyusb_board
    )

    #### pico_ice_sdk ####

    add_library(pico_ice_sdk INTERFACE)
    target_sources(pico_ice_sdk INTERFACE
        ice_sdk.c
    )
    target_include_directories(pico_ice_sdk INTERFACE ../include)
    target_link_libraries(pico_ice_sdk INTERFACE
        pico_ice_fpga
        pico_ice_smem
        pico_ice_usb
        pico_stdlib
    )
endif()
