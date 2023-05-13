import sys, os
sys.path.append(os.path.dirname(__file__) + "/pico-ice-sdk/amaranth")

# amaranth
from amaranth import *
from amaranth.sim import *

# local
from spi import *
from handshake import *
from spibone import *


__all__ = [ "Top" ]


class PeriReader(Elaboratable):

    def __init__(self):
        self.peri = HandshakePeriInInterface(width=32)

    def elaborate(self, platform):
        m = Module()

        with m.If(self.peri.req):
            m.d.comb += self.peri.ack.eq(1)

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


class SoC(Elaboratable):
    def __init__(self):
        self.spi = SPIPeriInterface()

    def elaborate(self, platform):
        m = Module()

        # Add a spi peripheral driving a spibone protocol parser

        m.submodules.spi = m_spi = SPIPeri()
        m.d.comb += m_spi.spi.connect(self.spi)

        m.submodules.spibone = m_spibone = Spibone()
        m.d.comb += m_spibone.rx.connect(m_spi.rx)
        m.d.comb += m_spibone.tx.connect(m_spi.tx)

        # Add downstream read and write bus to spibone

        m.submodules.readers = m_readers = HandshakeInterconnect()
        m_readers.set_ctrl(m_spibone.readers)

        m.submodules.writers = m_writers = HandshakeInterconnect()
        m_writers.set_ctrl(m_spibone.writers)

        # Add the peripherals to the read and write bus

        m.submodules.reader0 = m_reader0 = PeriReader()
        m_readers.add_peri(0x1000, m_reader0.peri)

        m.submodules.reader1 = m_reader1 = PeriReader()
        m_readers.add_peri(0x1001, m_reader1.peri)

        m.submodules.writer0 = m_writer0 = PeriWriter(value=0xF0)
        m_writers.add_peri(0x1000, m_writer0.peri)

        m.submodules.writer1 = m_writer1 = PeriWriter(value=0xF1)
        m_writers.add_peri(0x1001, m_writer1.peri)

        return m


def bench():
    global dut, xfer, data

    for i in range(len(xfer)):
        byte = data[i]

        for ii in range(8):
            bit = (byte >> ii) & 0x01

            yield dut.spi.clk.eq(0)
            yield dut.spi.cs.eq(xfer[i])
            yield dut.spi.copi.eq(bit)

            for _ in range(int(clk_freq_hz / spi_freq_hz)):
                yield

            yield dut.spi.clk.eq(1)

            for _ in range(int(clk_freq_hz / spi_freq_hz)):
                yield


if __name__ == "__main__":
    dut = SoC()

    clk_freq_hz = 10e6 # MHz
    spi_freq_hz = 2e6  # MHz

    xfer    = b"\x00\x01\x00\x01\x01\x01\x00\x01\x01\x01\x01\x00\x01\x00\x00\x00\x00"
    data    = b"\x00\x00\x00\xF0\xF0\xF0\x00\xF0\x12\x34\x56\x00\x78\x00\x00\x00\x00"

    sim = Simulator(dut)
    sim.add_clock(1 / clk_freq_hz)
    sim.add_sync_process(bench)
    with sim.write_vcd(vcd_file=f"{__file__[:-3]}.vcd"):
        sim.run()

