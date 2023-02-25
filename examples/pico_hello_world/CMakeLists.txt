add_executable(pico_hello_world
    main.c
    )
target_link_libraries(pico_hello_world
    pico_ice_sdk
    pico_stdio_usb
    )
pico_add_extra_outputs(pico_hello_world)
