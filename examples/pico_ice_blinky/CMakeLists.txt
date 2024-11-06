cmake_minimum_required(VERSION 3.13)

# set executable name
set(EXEC pico_ice_blinky)

# add the local files
add_executable(${EXEC}
    main.c
    )
target_link_libraries(${EXEC}
    pico_ice_sdk
    pico_stdlib
    )
target_include_directories(${EXEC} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    )
pico_add_extra_outputs(${EXEC})
pico_enable_stdio_usb(${EXEC} 0)
pico_enable_stdio_uart(${EXEC} 0)

set(VERILOG ${CMAKE_CURRENT_LIST_DIR}/top.v)
set(PCF ${CMAKE_CURRENT_LIST_DIR}/pico_ice.pcf)
add_custom_target(bitstream.h
    DEPENDS ${VERILOG}
    COMMAND yosys -p 'synth_ice40 -abc9 -top top -json bitstream.json' ${VERILOG} -q
    COMMAND nextpnr-ice40  --package sg48 --up5k --freq 48 --top top --pcf ${PCF} --json bitstream.json --asc bitstream.asc -q
    COMMAND icepack bitstream.asc bitstream.bin
    COMMAND python -c "\"print(', '.join(map(hex, open('bitstream.bin', 'rb').read())))\"" >bitstream.h
    )
add_dependencies(${EXEC} bitstream.h)
