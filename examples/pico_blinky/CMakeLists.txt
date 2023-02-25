add_executable(pico_blinky
    main.c
    )
target_link_libraries(pico_blinky
    pico_ice_sdk
    )
pico_add_extra_outputs(pico_blinky)
