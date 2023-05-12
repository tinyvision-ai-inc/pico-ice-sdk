# amaranth
from amaranth import *
from amaranth.sim import *
from amaranth.hdl.rec import *

# local
from handshake import *

__all__ = [
    "SPISignature",
    "SPICtrlInterface",
    "SPIPeriInterface",
    "SPIPeri"
]


class SPISignature(Record):
    def __init__(self, *, ctrl, peri):
        return super().__init__([
            ("clk",     1,  ctrl),
            ("copi",    1,  ctrl),
            ("cipo",    1,  peri),
            ("cs",      1,  ctrl),
        ])

class SPICtrlInterface(SPISignature):
    def __init__(self):
        super().__init__(ctrl=DIR_FANOUT, peri=DIR_FANIN)

class SPIPeriInterface(SPISignature):
    def __init__(self):
        super().__init__(peri=DIR_FANOUT, ctrl=DIR_FANIN)


class SPIPeri(Elaboratable):
    """
    SPI Peri with debounced inputs.
    """

    def __init__(self, *, debounce=8):
        self.debounce = debounce

        self.spi        = SPIPeriInterface()
        self.tx         = HandshakePeriInInterface(width=8)
        self.rx         = HandshakeCtrlOutInterface(width=8)
        self.selected   = Signal(1)
        self.deselected = Signal(1)

    def elaborate(self, platform):
        m = Module()
        shift_copi      = Signal(8)
        shift_cipo      = Signal(8)
        next_cipo       = Signal(8)
        next_copi       = Signal(8)
        last_clk        = Signal(1)
        last_cs         = Signal(1)
        sampling_edge   = Signal(1)
        updating_edge   = Signal(1)
        shift_count     = Signal(range(8))
        reload_rx       = Signal(1)
        reload_tx       = Signal(1)

        # detect the clock edges
        m.d.sync += last_clk.eq(self.spi.clk)
        m.d.sync += last_cs.eq(self.spi.cs)
        m.d.comb += self.selected.eq(~last_cs & self.spi.cs)
        m.d.comb += self.deselected.eq(last_cs & ~self.spi.cs)
        m.d.comb += sampling_edge.eq(~last_clk & self.spi.clk)
        m.d.comb += updating_edge.eq(last_clk & ~self.spi.clk)

        # bind shift registers to the I/O ports
        m.d.comb += self.spi.cipo.eq(shift_cipo[-1])

        self.tx.req.reset = 1

        # exchange data with the internal valid/ready module
        with m.If(self.tx.req & self.tx.ack):
            m.d.sync += next_cipo.eq(self.tx.data)
            m.d.sync += self.tx.req.eq(0)
        with m.If(self.rx.req & self.rx.ack):
            m.d.sync += self.rx.ack.eq(0)

        # shift data in and out on clock edges
        m.d.sync += reload_rx.eq(0)
        m.d.sync += reload_tx.eq(0)
        with m.If(self.spi.cs):
            with m.If(updating_edge):
                m.d.sync += shift_cipo.eq(Cat(0, shift_cipo))
                with m.If(shift_count == 0):
                    m.d.sync += reload_tx.eq(1)
            with m.If(sampling_edge):
                m.d.sync += shift_copi.eq(Cat(self.spi.copi, shift_copi[0:7]))
                m.d.sync += shift_count.eq(shift_count + 1)
                with m.If(shift_count == 7):
                    m.d.sync += reload_rx.eq(1)

        # refresh the data between the shift registers and valid/ready
        with m.If(reload_rx):
            m.d.sync += self.rx.ack.eq(1)
            m.d.sync += self.rx.data.eq(shift_copi)
        with m.If(reload_tx):
            m.d.sync += self.tx.req.eq(1)
            m.d.sync += shift_cipo.eq(next_cipo)
            m.d.sync += next_cipo.eq(0xFF)

        return m

    def write(self, data):
        return self.tx.write(data)


if __name__ == "__main__":
    dut = SPIPeri()

    clk_freq_hz = 10e6 # MHz
    spi_freq_hz = 2e6  # MHz

    copi = "_____ ##__##__##__##__##__##__##__##__########________####____####__________"
    clk  = "_______#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#______"
    cs   = "_____##################################################################_____"
    cipo = ""
    rx_data = bytearray()
    tx_data = b"\xFE\x55\x01\x8F\x00\x00\x00\x00"

    def bench():
        global cipo
        global rx_data
        global tx_data

        n = 0

        yield dut.rx.req.eq(1)

        for i in range(len(clk)):
            for _ in range(int(clk_freq_hz / spi_freq_hz)):
                yield

                yield dut.tx.data.eq(tx_data[n])
                yield dut.tx.ack.eq(1)
                if (yield dut.tx.req) == 1:
                    n += 1
                if (yield dut.rx.ack) == 1:
                    rx_data.append((yield dut.rx.data))

            cipo += "#" if (yield dut.spi.cipo) else "_"

            yield dut.spi.copi.eq(copi[i] == "#")
            yield dut.spi.clk.eq(clk[i] == "#")
            yield dut.spi.cs.eq(cs[i] == "#")

    sim = Simulator(dut)
    sim.add_clock(1 / clk_freq_hz)
    sim.add_sync_process(bench)
    with sim.write_vcd(vcd_file=f"{__file__[:-3]}.vcd"):
        sim.run()

    print(f"cipo={cipo}")
    print(f"copi={rx_data}")
    assert rx_data == b"\xAA\xAA\xF0\xCC"
