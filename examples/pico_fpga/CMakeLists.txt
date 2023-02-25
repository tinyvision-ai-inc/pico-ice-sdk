add_executable(pico_fpga
    main.c
    )
target_link_libraries(pico_fpga
    pico_ice_sdk
    )
pico_add_extra_outputs(pico_fpga)
