import os
import subprocess
from amaranth.build import *
from amaranth.vendor.lattice_ice40 import *
from amaranth_boards.resources import *


__all__ = ["PicoIcePlatform"]


class PicoIcePlatform(LatticeICE40Platform):
    device      = "iCE40UP5K"
    package     = "SG48"
    default_clk = "SB_HFOSC"
    hfosc_div   = 1
    resources   = [
        *LEDResources(pins="39 40", invert=True, attrs=Attrs(IO_STANDARD="SB_LVCMOS")),
        Resource("led_g", 0, PinsN("39", dir="o"), Attrs(IO_STANDARD="SB_LVCMOS")),
        Resource("led_b", 0, PinsN("40", dir="o"), Attrs(IO_STANDARD="SB_LVCMOS")),
        # led_r is used as a cs_n pin for iCE40 <-> RP2040 I/O
        #Resource("led_r", 0, PinsN("41", dir="o"), Attrs(IO_STANDARD="SB_LVCMOS")),
        *ButtonResources(pins="11", invert=True,
            attrs=Attrs(IO_STANDARD="SB_LVCMOS")),
        *SPIFlashResources(0, cs_n="16", clk="15", copi="14", cipo="17",
            attrs=Attrs(IO_STANDARD="SB_LVCMOS")),
        SPIResource("sram", 0, cs_n="37", clk="15", copi="14", cipo="17",
            attrs=Attrs(IO_STANDARD="SB_LVCMOS"), role="controller"),
        SPIResource("rp2040", 0, cs_n="41", clk="15", copi="14", cipo="17",
            attrs=Attrs(IO_STANDARD="SB_LVCMOS"), role="peripheral"),
    ]
    connectors = [
        Connector("pmod", 1, " 4  2 47 45 - -  3 48 46 44 - -"),
        Connector("pmod", 2, "43 38 34 31 - - 42 36 32 28 - -"),
        Connector("pmod", 3, "25 19 27 21 - - 23 18 26 20 - -"),
    ]

    def toolchain_program(self, products, name, dfu_vid="1209", dfu_pid="b1c0", dfu_alt=0):
        dfu_util = os.environ.get("DFU_UTIL", "dfu-util")
        dfu_args = ["-d", f"{dfu_vid}:{dfu_pid}", "-a", str(dfu_alt)]
        with products.extract(f"{name}.bin") as bitstream_filename:
            subprocess.check_call([dfu_util, "-D", bitstream_filename] + dfu_args)
