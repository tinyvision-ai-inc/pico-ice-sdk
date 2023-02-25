add_executable(pico_blinky_cplusplus
    main.cpp
    )
target_link_libraries(pico_blinky_cplusplus
    pico_ice_sdk
    pico_ice_usb
    )
target_include_directories(pico_blinky_cplusplus PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
    )
pico_add_extra_outputs(pico_blinky_cplusplus)
