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
from spibone import *


__all__ = [ "Top" ]


class PeriReader(Elaboratable):

    def __init__(self, value=0x55):
        self.peri = HandshakePeriInInterface(width=32)
        self.value = value

    def elaborate(self, platform):
        m = Module()

        with m.If(self.peri.req):
            m.d.comb += self.peri.ack.eq(1)
            m.d.comb += self.peri.data.eq(self.value)

        return m


class PeriWriter(Elaboratable):

    def __init__(self, value=0x55):
        self.peri = HandshakePeriOutInterface(width=32)
        self.value = value

    def elaborate(self, platform):
        m = Module()

        with m.If(self.peri.req):
            m.d.comb += self.peri.ack.eq(1)
            m.d.comb += self.peri.data.eq(self.value)

        return m


class Top(Elaboratable):

    def elaborate(self):
        m = Module()

        rp2040 = platform.request("rp2040", 0)
        debug = platform.request("debug", 0)

        m.submodules.spi = m_spi = SPIPeri()
        m.d.comb += m_spi.spi.cs.eq(rp2040.cs)
        m.d.comb += m_spi.spi.copi.eq(m_spi.spi.copi)
        m.d.comb += rp2040.cipo.eq(m_spi.spi.cipo)
        m.d.comb += m_spi.spi.clk.eq(rp2040.clk)

        m.submodules.spibone = m_spibone = Spibone()
        m.d.comb += m_spibone.rx.connect(m_spi.rx)
        m.d.comb += m_spibone.tx.connect(m_spi.tx)

        m.submodules.readers = m_readers = HandshakeInterconnect()
        m_readers.set_ctrl(m_spibone.readers)

        m.submodules.writers = m_writers = HandshakeInterconnect()
        m_writers.set_ctrl(m_spibone.writers)

        m.submodules.reader0 = m_reader0 = PeriReader(value=0xF0)
        m_readers.add_peri(0x1000, m_reader0.peri)

        m.submodules.reader1 = m_reader1 = PeriReader(value=0xF1)
        m_readers.add_peri(0x1001, m_reader1.peri)

        m.submodules.writer0 = m_writer0 = PeriReader(value=0xF0)
        m_writers.add_peri(0x1000, m_writer0.peri)

        m.submodules.writer1 = m_writer1 = PeriReader(value=0xF1)
        m_writers.add_peri(0x1001, m_writer1.peri)

        return m


if __name__ == "__main__":
    platform = PicoIcePlatform()
    platform.add_resources([
        Resource("debug", 0, Pins("1 2 3 4 7 8 9 10", conn=("pmod", 3)))
    ])
    platform.build(Top, do_program=True, program_opts={"dfu_alt": 1})
