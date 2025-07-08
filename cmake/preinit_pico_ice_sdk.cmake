cmake_minimum_required(VERSION 3.13)

add_library(pico_ice_preinit_common INTERFACE)

if(NOT DEFINED PICO_BOARD OR PICO_BOARD STREQUAL pico_ice)
    message(WARNING "if using the pico2-ice, add -DPICO_BOARD=pico2_ice at the end of the cmake command")
    set(PICO_BOARD pico_ice)
    target_compile_definitions(pico_ice_preinit_common INTERFACE PICO_ICE)
endif()

if(PICO_BOARD STREQUAL pico2_ice)
    if(NOT DEFINED PICO_PLATFORM)
        set(PICO_PLATFORM rp2350)
    endif()
    target_compile_definitions(pico_ice_preinit_common INTERFACE PICO2_ICE)
endif()

list(APPEND PICO_BOARD_HEADER_DIRS "${CMAKE_CURRENT_LIST_DIR}/../include/boards")

