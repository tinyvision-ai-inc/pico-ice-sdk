add_executable(pico_sram
    main.c
    usb_descriptors.c
    )
target_link_libraries(pico_sram
    pico_ice_sdk
    pico_ice_usb
    )
target_include_directories(pico_sram PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
    )
pico_add_extra_outputs(pico_sram)
