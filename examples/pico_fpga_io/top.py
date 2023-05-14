import sys, os
sys.path.append(os.path.dirname(__file__) + "/pico-ice-sdk/amaranth")

# amaranth
from amaranth import *
from amaranth.build import *
from amaranth.cli import main
from amaranth_boards.resources import *

# pico-ice-sdk
from pico_ice import *
from debouncer import *

# local
from soc import *


__all__ = [ "Top" ]


class Top(Elaboratable):

    def elaborate(self):
        m = Module()

        rp2040 = platform.request("rp2040", 0)

        # debounce SPI signals, should really be needed?
        m.submodules.spi_cs   = m_spi_cs   = Debouncer(width=1)
        m.d.comb += m_spi_cs.i.eq(rp2040.cs)
        m.submodules.spi_clk  = m_spi_clk  = Debouncer(width=1)
        m.d.comb += m_spi_clk.i.eq(rp2040.clk)
        m.submodules.spi_copi = m_spi_copi = Debouncer(width=1)
        m.d.comb += m_spi_copi.i.eq(rp2040.copi)

        # instantiate the main SoC module
        m.submodules.soc = m_soc = SoC()
        m.d.comb += m_soc.spi.cs.eq(m_spi_cs.o)
        m.d.comb += m_soc.spi.copi.eq(m_spi_copi.o)
        m.d.comb += m_soc.spi.clk.eq(m_spi_clk.o)
        m.d.comb += rp2040.cipo.eq(m_soc.spi.cipo)

        return m


if __name__ == "__main__":
    platform = PicoIcePlatform()
    platform.add_resources([
        Resource("debug", 0, Pins("1 2 3 4 7 8 9 10", conn=("pmod", 3), dir="o"))
    ])
    platform.build(Top, do_program=True, program_opts={"dfu_alt": 1})
