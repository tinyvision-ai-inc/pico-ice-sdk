cmake_minimum_required(VERSION 3.13)

include(${CMAKE_CURRENT_SOURCE_DIR}/pico-ice-sdk/cmake/preinit_pico_ice_sdk.cmake)

# import the pico-sdk
set(PICO_SDK_PATH ${CMAKE_CURRENT_SOURCE_DIR}/pico-sdk/)
include(pico_sdk_import.cmake)

# configure the pico-sdk project
project(rp2_usb_uart C CXX ASM)
pico_sdk_init()

# add the pico-ice-sdk
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/pico-ice-sdk/)

# add the local files
add_executable(${CMAKE_PROJECT_NAME}
    main.c
    usb_descriptors.c
    )
target_link_libraries(${CMAKE_PROJECT_NAME}
    pico_ice_sdk
    pico_ice_usb
    pico_stdio_usb
    )
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
    )
pico_add_extra_outputs(${CMAKE_PROJECT_NAME})
