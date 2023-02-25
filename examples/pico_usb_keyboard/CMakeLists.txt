add_executable(pico_usb_keyboard
    main.c
    )
target_link_libraries(pico_usb_keyboard
    pico_ice_sdk
    tinyusb_host
    )
target_include_directories(pico_usb_keyboard PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
    )
pico_add_extra_outputs(pico_usb_keyboard)
