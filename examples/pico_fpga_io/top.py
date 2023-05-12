import sys, os
sys.path.append(os.path.dirname(__file__) + "/pico-ice-sdk/amaranth")

# amaranth
from amaranth import *
from amaranth.build import *
from amaranth.cli import main
from amaranth_boards.resources import *

# pico-ice-sdk
from pico_ice import *

# local
from spi import *
from handshake import *
from bus import *


__all__ = [ "Top" ]


class Top(Elaboratable):
    def elaborate(self):
        m = Module()

        rp2040 = platform.request("rp2040", 0)
        debug = platform.request("debug", 0)

        m.submodules.spi_peri = spi_peri = SPIPeri()

        m.d.comb += spi_peri.spi.cs.eq(rp2040.cs)
        m.d.comb += spi_peri.spi.copi.eq(spi_peri.spi.copi)
        m.d.comb += rp2040.cipo.eq(spi_peri.spi.cipo)
        m.d.comb += spi_peri.spi.clk.eq(rp2040.clk)

        return m


if __name__ == "__main__":
    platform = PicoIcePlatform()
    platform.build(Top, do_program=True, program_opts={"dfu_alt": 1})
