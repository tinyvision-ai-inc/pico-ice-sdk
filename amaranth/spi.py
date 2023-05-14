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
        shift_cipo      = Signal(8, reset=0xFF)
        shift_count     = Signal(range(8))
        last_clk        = Signal(1)
        last_cs         = Signal(1)
        sampling_edge   = Signal(1)
        updating_edge   = Signal(1)
        tx_data         = Signal(8, reset=0xFF)
        rx_data         = Signal(8)
        get_tx_data     = Signal(1, reset=1)
        put_rx_data     = Signal(1)

        # detect the clock edges
        m.d.sync += last_clk.eq(self.spi.clk)
        m.d.sync += last_cs.eq(self.spi.cs)
        m.d.comb += self.selected.eq(~last_cs & self.spi.cs)
        m.d.comb += self.deselected.eq(last_cs & ~self.spi.cs)
        m.d.comb += sampling_edge.eq(~last_clk & self.spi.clk)
        m.d.comb += updating_edge.eq(last_clk & ~self.spi.clk)

        # bind shift registers to the I/O ports
        m.d.comb += self.spi.cipo.eq(shift_cipo[-1])

        # shift data in and out on clock edges
        with m.If(self.spi.cs):
            with m.If(updating_edge):
                m.d.sync += shift_cipo.eq(Cat(0, shift_cipo))
                with m.If(shift_count == 0):
                    m.d.sync += shift_cipo.eq(tx_data)
                    m.d.sync += tx_data.eq(0xFF)
                    m.d.sync += get_tx_data.eq(1)
            with m.If(sampling_edge):
                next_shift_copi = Cat(self.spi.copi, shift_copi[0:7])
                m.d.sync += shift_copi.eq(next_shift_copi)
                m.d.sync += shift_count.eq(shift_count + 1)
                with m.If(shift_count == 7):
                    m.d.sync += rx_data.eq(next_shift_copi)
                    m.d.sync += put_rx_data.eq(1)

        # receive data to transmit to SPI
        with m.If(get_tx_data):
            with m.If(self.tx.req):
                self.tx.read(m, tx_data)
                m.d.sync += get_tx_data.eq(0)

        # send data received from SPI
        with m.If(put_rx_data):
            self.rx.write(m, rx_data)
            with m.If(self.rx.ack):
                m.d.sync += put_rx_data.eq(0)

        return m


if __name__ == "__main__":
    dut = SPIPeri()

    clk_freq_hz = 10e6 # MHz
    spi_freq_hz = 2e6  # MHz

    copi = "______##__##__##__##__##__##__##__##__########________####____####__________"
    clk  = "_______#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#______"
    cs   = "_____##################################################################_____"
    cipo = ""
    rx = bytearray()
    tx = b"\xFE\x55\x01\x8F\x00\x00\x00\x00"

    def bench():
        global cs, clk, copi, cipo, rx, tx

        n = 0
        yield dut.rx.req.eq(1)

        for i in range(len(clk)):
            for _ in range(int(clk_freq_hz / spi_freq_hz)):
                yield dut.tx.data.eq(tx[n])
                yield dut.tx.req.eq(1)
                if (yield dut.tx.ack) == 1:
                    n += 1

                yield dut.rx.ack.eq(0)
                if (yield dut.rx.req) == 1:
                    rx.append((yield dut.rx.data))
                    yield dut.rx.ack.eq(1) # todo: why is this offset by one clock?

                yield



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
    print(f"copi={rx}")
    assert rx == b"\xAA\xAA\xF0\xCC"
