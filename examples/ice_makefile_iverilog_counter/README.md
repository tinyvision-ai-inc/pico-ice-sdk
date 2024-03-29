# ice_makefile_iverilog_counter

Example project using a standard [Makefile](https://en.wikipedia.org/wiki/Make_%28software%29)
to build a project with an [Icarus Verilog](https://steveicarus.github.io/iverilog/) simulation test bench.

It needs [oss-cad-suite](https://github.com/YosysHQ/oss-cad-suite-build) installed.
See the [doc](https://pico-ice.tinyvision.ai/using_oss_cad_suite.html) for more.

Build with `make`. This should simulate the design, producing a `iverilog.vcd` that can be browsed with `gtkwave iverilog.vcd`.

`ice40.sv` wraps `top.sv` and can be deployed to the pico-ice with `make prog`, and `make gateware.uf2` to generate an
[uf2 image](https://pico-ice.tinyvision.ai/programming_the_fpga.html#using-a-drag-drop-or-file-copy-scheme)
to program with drag-and-drop.

A very complete `Makefile` example is provided for the UPduino v3 by Xark:
<https://github.com/XarkLabs/upduino-example/>
