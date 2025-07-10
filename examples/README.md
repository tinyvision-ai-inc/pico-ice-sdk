# pico-ice examples

This directory contains examples for using the RP2040 and iCE40 of the pico-ice board.

- The `rp2_...` examples show usage of the `pico-ice-sdk` in C and C++
- The `ice_...` examples show usage of Hardware Description Language to [load on the iCE40](https://pico-ice.tinyvision.ai/programming_the_fpga.html)
- The `rp2_ice_...` examples show usage of combined firmware/gateware to upload to the FPGA as a single combined image.

To use any example, make sure to clone this repository recursively so that it contains all dependencies.

To turn an example into a project:

1. Copy the example directory you want to use.
2. Remove the `pico-ice-sdk` and `pico-sdk` symbolic links
3. Add the `pico-ice-sdk` and `pico-sdk` as submodule
4. Update the submodule dependencies with `git -C <module> update --init`
5. Build your new application with CMake.
