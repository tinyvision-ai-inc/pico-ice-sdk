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
from soc import *


__all__ = [ "Top" ]


class Top(Elaboratable):

    def elaborate(self):
        m = Module()

        rp2040 = platform.request("rp2040", 0)

        m.submodules.soc = m_soc = SoC()
        m.d.comb += m_soc.spi.cs.eq(rp2040.cs)
        m.d.comb += m_soc.spi.copi.eq(rp2040.copi)
        m.d.comb += rp2040.cipo.eq(m_soc.spi.cipo)
        m.d.comb += m_soc.spi.clk.eq(rp2040.clk)

        return m


if __name__ == "__main__":
    platform = PicoIcePlatform()
    platform.add_resources([
        Resource("debug", 0, Pins("1 2 3 4 7 8 9 10", conn=("pmod", 3), dir="o"))
    ])
    platform.build(Top, do_program=True, program_opts={"dfu_alt": 1})
