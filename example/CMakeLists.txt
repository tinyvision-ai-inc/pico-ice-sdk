add_custom_target(pico_ice_all_examples)
add_dependencies(pico_ice_all_examples
    pico_blinky
    pico_blinky_cplusplus
    pico_empty
    pico_flash_io
    pico_fpga
    pico_hello_world
    pico_ssram
)

add_subdirectory(pico-blinky)
add_subdirectory(pico-blinky-cplusplus)
add_subdirectory(pico-empty)
add_subdirectory(pico-flash-io)
add_subdirectory(pico-fpga)
add_subdirectory(pico-hello-world)
add_subdirectory(pico-ssram)
