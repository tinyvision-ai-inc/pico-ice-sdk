# rp2_ice_i2c

Example of integration between the iCE40 FPGA and the RP2350 MCU.

The RP2350 sends a continuous I2C scan and the FPGA acknowledges it which the RP2350 detects.

It needs [oss-cad-suite](https://github.com/YosysHQ/oss-cad-suite-build) installed.

For instance, if downloading oss-cad-suite in `~/oss-cad-suite`

```
source ~/oss-cad-suite/environment
```

Then you may be able to build it like a normal pico-sdk project:

```
cmake -B build -DPICO_BOARD=pico2_ice
cmake --build build
```

At this point, the [`iverilog`](https://steveicarus.github.io/iverilog/) tool will be launched,
simulating the program and producing a `build/top_simulation.vcd` output.
You can use tools such as [`gtkwave`](https://github.com/gtkwave/gtkwave) to inspect the output.

Then, you may program the RTL into your board:

```
picotool load build/rp2_ice_i2c.uf2
picotool reboot
```
