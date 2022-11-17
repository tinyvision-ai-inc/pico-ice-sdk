# This is a copy of {PICO_ICE_SDK_PATH}/pico_ice_sdk_import.cmake
include(FetchContent)

if (NOT DEFINED ENV{PICO_ICE_SDK_PATH})
    message("Downloading Raspberry Pi Pico SDK")
    FetchContent_Declare(
        pico-sdk
        GIT_REPOSITORY https://github.com/raspberrypi/pico-sdk
        GIT_TAG master
        GIT_SHALLOW true
        GIT_SUBMODULES_RECURSE false
    )
    FetchContent_Populate(pico-sdk)
    set(PICO_SDK_PATH ${pico-sdk_SOURCE_DIR} CACHE PATH "Path to the Raspberry Pi Pico SDK")
endif()

if (NOT DEFINED ENV{PICO_ICE_SDK_PATH})
    message("Downloading Pico-Ice SDK")
    FetchContent_Declare(
        pico-ice-sdk
        GIT_REPOSITORY https://github.com/tinyvision-ai-inc/pico-ice-sdk
        GIT_TAG develop
        GIT_SHALLOW true
        GIT_SUBMODULES_RECURSE false
    )
    FetchContent_Populate(pico-ice-sdk)
    set(PICO_ICE_SDK_PATH ${pico-ice-sdk_SOURCE_DIR} CACHE PATH "Path to the Pico-Ice SDK")
endif()

include(${PICO_ICE_SDK_PATH}/cmake/pico_ice_sdk_init.cmake)
include(${PICO_SDK_PATH}/pico_sdk_init.cmake)
add_subdirectory(${PICO_ICE_SDK_PATH})
