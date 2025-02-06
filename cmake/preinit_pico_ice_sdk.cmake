cmake_minimum_required(VERSION 3.13)

if (NOT DEFINED PICO_BOARD)
    set(PICO_BOARD pico_ice)
endif()
if (PICO_BOARD STREQUAL pico2_ice)
    set(PICO_PLATFORM rp2350)
endif()
list(APPEND PICO_BOARD_HEADER_DIRS "${CMAKE_CURRENT_LIST_DIR}/../include/boards")

