cmake_minimum_required(VERSION 3.13)

add_library(pico_ice_preinit_common INTERFACE)

if (NOT DEFINED PICO_BOARD)
    set(PICO_BOARD pico_ice)
    target_compile_definitions(pico_ice_preinit_common INTERFACE PICO_ICE)
endif()
if (PICO_BOARD STREQUAL pico2_ice)
    set(PICO_PLATFORM rp2350)
    target_compile_definitions(pico_ice_preinit_common INTERFACE PICO2_ICE)
endif()
list(APPEND PICO_BOARD_HEADER_DIRS "${CMAKE_CURRENT_LIST_DIR}/../include/boards")

