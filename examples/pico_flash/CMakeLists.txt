add_executable(pico_flash
    main.c
    )
target_link_libraries(pico_flash
    pico_ice_sdk
    pico_stdio_usb
    )
pico_add_extra_outputs(pico_flash)
