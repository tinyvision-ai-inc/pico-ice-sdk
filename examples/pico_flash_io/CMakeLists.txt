add_executable(pico_usb_flash_io
    main.c
    )
target_link_libraries(pico_usb_flash_io
    pico_ice_sdk
    pico_stdio_usb
    )
pico_add_extra_outputs(pico_usb_flash_io)
