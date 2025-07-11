cmake_minimum_required(VERSION 3.13)

include(${CMAKE_CURRENT_SOURCE_DIR}/pico-ice-sdk/cmake/preinit_pico_ice_sdk.cmake)

# import the pico-sdk
set(PICO_SDK_PATH ${CMAKE_CURRENT_SOURCE_DIR}/pico-sdk/)
include(pico_sdk_import.cmake)

# configure the pico-sdk project
project(rp2_ice_blinky C CXX ASM)
pico_sdk_init()

# add the pico-ice-sdk
set(PICO_ICE_SDK_PATH ${CMAKE_CURRENT_SOURCE_DIR}/pico-ice-sdk/)
add_subdirectory(${PICO_ICE_SDK_PATH})

# add the local files
add_executable(${CMAKE_PROJECT_NAME}
    main.c
    )
target_link_libraries(${CMAKE_PROJECT_NAME}
    pico_ice_sdk
    pico_stdio_usb
    hardware_i2c
    )
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    )
pico_add_extra_outputs(${CMAKE_PROJECT_NAME})
#pico_enable_stdio_usb(${CMAKE_PROJECT_NAME} 1)
#pico_enable_stdio_uart(${CMAKE_PROJECT_NAME} 0)

set(VERILOG_COMMON_SRC
    ${PICO_ICE_SDK_PATH}/rtl/i2c_target.v
    ${PICO_ICE_SDK_PATH}/rtl/i2c_target_mac.v
    ${CMAKE_CURRENT_LIST_DIR}/rtl/main.v
    ${CMAKE_CURRENT_LIST_DIR}/rtl/dual_7seg_display.v
    )
set(VERILOG_SIMULATION_SRC
    ${CMAKE_CURRENT_LIST_DIR}/rtl/top_simulation.v
    ${VERILOG_COMMON_SRC}
    )
set(VERILOG_SYNTHESIS_SRC
    ${CMAKE_CURRENT_LIST_DIR}/rtl/top_synthesis_ice40.v
    ${VERILOG_COMMON_SRC}
    )

add_custom_target(bitstream.h
    DEPENDS ${VERILOG_SIMULATION_SRC}
    DEPENDS ${VERILOG_SYNTHESIS_SRC}

    # Run the simulation first to allow comparing simulation and real output

    COMMAND
        iverilog -g2012 -Wall -o top_simulation.vvp ${VERILOG_SIMULATION_SRC}

    COMMAND
        vvp top_simulation.vvp top_simulation.vcd

    # Then run the synthesis

    COMMAND
        yosys --quiet --commands "synth_ice40 -abc9 -top top -json bitstream.json"
            ${VERILOG_SYNTHESIS_SRC}
    COMMAND
        nextpnr-ice40 --quiet --package sg48 --up5k --freq 24 --top top
            --pcf ${PICO_ICE_SDK_PATH}/rtl/${PICO_BOARD}.pcf
            --json bitstream.json
            --asc bitstream.asc

    # Generate a binary and turn it into a header for inclusion in the firmware

    COMMAND
        icepack bitstream.asc bitstream.bin

    COMMAND
        python ${CMAKE_CURRENT_LIST_DIR}/bin2header.py bitstream.bin >bitstream.h

    )

add_dependencies(${CMAKE_PROJECT_NAME} bitstream.h)
