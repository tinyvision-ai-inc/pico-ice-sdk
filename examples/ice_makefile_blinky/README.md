# ice_makefile_blinky

Example project using a standard [Makefile](https://en.wikipedia.org/wiki/Make_%28software%29)
to build a project.

It needs a local [oss-cad-suite](https://github.com/YosysHQ/oss-cad-suite-build) toolchain installed,
or at least `yosys`, `nextpnr-ice40`, `icepack` and `python` in the execution path.

Build with `make` and deploy it onto the pico-ice with `make prog`, and `make gateware.uf2` to generate an
[uf2 image](https://pico-ice.tinyvision.ai/programming_the_fpga.html#using-a-drag-drop-or-file-copy-scheme)
to program with drag-and-drop.

See the [doc](https://pico-ice.tinyvision.ai/using_oss_cad_suite.html) for more.

A very complete `Makefile` example is provided for the UPduino v3 by Xark:
<https://github.com/XarkLabs/upduino-example/>
