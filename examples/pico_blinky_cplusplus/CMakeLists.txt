cmake_minimum_required(VERSION 3.13)

# set executable name
set(EXEC pico_blinky_cplusplus)

# add the local files
add_executable(${EXEC}
    main.cpp
    )
target_link_libraries(${EXEC}
    pico_ice_sdk
    pico_stdlib
    pico_ice_usb
    )
target_include_directories(${EXEC} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
    )
pico_add_extra_outputs(${EXEC})
pico_enable_stdio_usb(${EXEC} 0)
pico_enable_stdio_uart(${EXEC} 0)
