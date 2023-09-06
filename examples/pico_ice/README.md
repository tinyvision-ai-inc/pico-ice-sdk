# pico_ice_blinky

Example of a basic firmware that embeds the FPGA bitstream inside a same image, to be programmed onto the RP2040.

The RP2040 the further program the iCE40 with that embedded image, and the flash chip does not get used at all.

It assumes a local [oss-cad-suite](https://github.com/YosysHQ/oss-cad-suite-build) toolchain installed,
or at least `yosys`, `nextpnr-ice40`, `icepack` and `python` in the execution path.

Originally from <https://github.com/janrinze/pico-ice-tests>
