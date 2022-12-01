# We do not really use C++, but CXX is still required for using the
# raspberrypi/pico-sdk. This also enable C++ support.
enable_language(C CXX)

set(PICO_ICE_SDK_PATH ${CMAKE_CURRENT_LIST_DIR})
list(APPEND PICO_BOARD_HEADER_DIRS ${PICO_ICE_SDK_PATH}/include/boards)

# Add the pico-ice-sdk as a CMake STATIC library, otherwise it will link
# the raspberrypi/pico-sdk twice
add_library(pico_ice_sdk STATIC
    ${PICO_ICE_SDK_PATH}/src/ssram.c
    ${PICO_ICE_SDK_PATH}/src/flash.c
    ${PICO_ICE_SDK_PATH}/src/fpga.c
    ${PICO_ICE_SDK_PATH}/src/init.c
    ${PICO_ICE_SDK_PATH}/src/tinyuf2/board_pico_ice.c
    ${PICO_ICE_SDK_PATH}/src/tinyuf2/ghostfat.c
    ${PICO_ICE_SDK_PATH}/src/tinyuf2/main.c
    ${PICO_ICE_SDK_PATH}/src/tinyuf2/msc.c
    ${PICO_ICE_SDK_PATH}/src/usb.c
    ${PICO_ICE_SDK_PATH}/src/usb_descriptors.c
)
target_include_directories(pico_ice_sdk PUBLIC ${PICO_ICE_SDK_PATH}/include)

# This is in order to access the headers of the raspberrypi/pico-sdk, which
# will add the -I flags.
target_link_libraries(pico_ice_sdk 
    tinyusb_device
    tinyusb_board
    pico_stdlib
    hardware_spi
    hardware_uart
    hardware_flash
    hardware_dma
)
