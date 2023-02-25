add_executable(pico_cram
    main.c
    )
target_link_libraries(pico_cram
    pico_ice_sdk
    )
pico_add_extra_outputs(pico_cram)
