cmake_minimum_required(VERSION 3.13)

# set executable name
set(EXEC pico_usb_fpga)

# add the local files
add_executable(${EXEC}
    main.c
    usb_descriptors.c
    )
target_link_libraries(${EXEC}
    pico_ice_sdk
    pico_stdlib
    pico_ice_usb
    pico_stdio_usb
    )
target_include_directories(${EXEC} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
    )
pico_add_extra_outputs(${EXEC})
