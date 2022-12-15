cmake_minimum_required(VERSION 3.13)

if (NOT DEFINED PICO_SDK_PATH)
    set(PICO_SDK_PATH "${CMAKE_CURRENT_LIST_DIR}/pico-sdk")
endif()

set(PICO_ICE_SDK_PATH "${CMAKE_CURRENT_LIST_DIR}")

if (NOT DEFINED PICO_BOARD)
    set(PICO_BOARD pico_ice)
endif()

list(APPEND PICO_BOARD_HEADER_DIRS "${PICO_ICE_SDK_PATH}/include/boards")

include("${PICO_SDK_PATH}/pico_sdk_init.cmake")
project(pico_ice_sdk C CXX ASM)
pico_sdk_init()

add_subdirectory(src)
add_subdirectory(example EXCLUDE_FROM_ALL)
