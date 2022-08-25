# This is a copy of {PICO_ICE_SDK_PATH}/cmake/pico_ice_sdk_import.cmake
include(FetchContent)

FetchContent_Declare(
    pico-sdk
    GIT_REPOSITORY https://github.com/raspberrypi/pico-sdk
    GIT_TAG master
    GIT_SHALLOW true
    GIT_SUBMODULES_RECURSE false
)

FetchContent_Declare(
    pico-ice-sdk
    GIT_REPOSITORY https://github.com/tinyvision-ai-inc/pico-ice-sdk
    GIT_TAG dev
    GIT_SHALLOW true
    GIT_SUBMODULES_RECURSE false
)

if(NOT pico-sdk)
    message("Downloading Raspberry Pi Pico SDK")
    FetchContent_Populate(pico-sdk)
    set(PICO_SDK_PATH ${pico-sdk_SOURCE_DIR})
endif()

if(NOT pico-ice-sdk)
    message("Downloading Pico-Ice SDK")
    FetchContent_Populate(pico-ice-sdk)
    set(PICO_ICE_SDK_PATH ${pico-ice-sdk_SOURCE_DIR})
endif()

set(PICO_SDK_PATH ${PICO_SDK_PATH} CACHE PATH "Path to the Raspberry Pi Pico SDK")
set(PICO_ICE_SDK_PATH ${PICO_ICE_SDK_PATH} CACHE PATH "Path to the Pico-Ice SDK")

include(${PICO_SDK_PATH}/pico_sdk_init.cmake)
add_subdirectory(${PICO_ICE_SDK_PATH})
