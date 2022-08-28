# We do not really use C++, but CXX is still required for using the
# raspberrypi/pico-sdk. This also enable C++ support.
enable_language(C CXX)

# Add the pico-ice-sdk as a CMake STATIC library, otherwise it will link
# the raspberrypi/pico-sdk twice
add_library(pico_ice_sdk STATIC
    ${PICO_ICE_SDK_PATH}/src/flash.c
)

target_include_directories(pico_ice_sdk PUBLIC include)

# This is in order to access the headers of the raspberrypi/pico-sdk, which
# will add the -I flags.
target_link_libraries(pico_ice_sdk pico_stdio_uart pico_stdlib hardware_spi)