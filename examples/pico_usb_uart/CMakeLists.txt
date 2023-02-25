add_executable(pico_usb_uart
    main.c
    usb_descriptors.c
    )
target_link_libraries(pico_usb_uart
    pico_ice_sdk
    pico_ice_usb
    )
target_include_directories(pico_usb_uart PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
    )
pico_add_extra_outputs(pico_usb_uart)
