# amaranth
from amaranth import *
from amaranth.hdl.rec import *


__all__ = [
    "HandshakeSignature",
    "HandshakeCtrlInInterface",
    "HandshakeCtrlOutInterface",
    "HandshakePeriInInterface",
    "HandshakePeriOutInterface",
    "HandshakeInterconnect",
]


class HandshakeSignature(Record):
    def __init__(self, *, width, ack, req, data):
        super().__init__([
            ("data",    width,  data),
            ("req",     1,      req),
            ("ack",     1,      ack),
        ])


class HandshakeCtrlInInterface(HandshakeSignature):
    def __init__(self, *, width):
        super().__init__(width=width, req=DIR_FANOUT, ack=DIR_FANIN, data=DIR_FANIN)

    def read(self, data):
        return [
            data.eq(self.data),
            self.req.eq(1),
        ]


class HandshakeCtrlOutInterface(HandshakeSignature):
    def __init__(self, *, width):
        super().__init__(width=width, req=DIR_FANOUT, ack=DIR_FANIN, data=DIR_FANOUT)

    def write(self, data):
        return [
            self.data.eq(data),
            self.req.eq(1),
        ]


class HandshakePeriInInterface(HandshakeSignature):
    def __init__(self, *, width):
        super().__init__(width=width, ack=DIR_FANOUT, req=DIR_FANIN, data=DIR_FANIN)

class HandshakePeriOutInterface(HandshakeSignature):
    def __init__(self, *, width):
        super().__init__(width=width, ack=DIR_FANOUT, req=DIR_FANIN, data=DIR_FANOUT)


class HandshakeInterconnect(Elaboratable):
    def __init__(self, addr=32, data=32):
        self.ctrl = HandshakeCtrlOutInterface(width=data)
        self.peri = {}
        self.addr = Signal(addr)
        self.ack = self.ctrl.ack

    def add_peri(self, addr, peri):
        assert addr not in self.peri
        self.peri[addr] = peri

    def elaborate(self, platform):
        m = Module()

        with m.Switch(self.addr):
            for addr in self.peri:
                with m.Case(addr):
                    m.d.comb += self.ctrl.connect(self.peri[addr])
        return m

    def read(self, addr, data):
        return [
            self.addr.eq(addr),
            self.ctrl.read(data),
        ]

    def write(self, addr, data):
        return [
            self.addr.eq(addr),
            self.ctrl.write(data),
        ]


if __name__ == "__main__":
    dut = HandshakeInterconnect(addr=8, data=8)

    dut.ctrl.connect(HandshakeCtrlOutInterface(width=8))
    dut.add_peri(0xF0, HandshakePeriInInterface(width=8))
    dut.add_peri(0xF1, HandshakePeriInInterface(width=8))

    clk_freq_hz = 10e6 # MHz

    ctrl_req  = b"\x00\x01\x00\x00\x01\x00\x00\x00\x00\x01\x01\x01\x00\x01\x01\x00"
    ctrl_addr = b"\x00\xF0\x00\x00\xF1\x00\xF0\xF1\x00\xF0\xF0\xF0\x00\xF1\xF0\x00"
    ctrl_data = b"\x00\x11\x00\x00\x22\x00\x00\x00\x00\x33\x33\x33\x00\x44\x55\x00"
                       ###         ###                 ### ### ###     ### ###
    peri0_ack = b"\x00\x01\x00\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x01\x00"
    peri1_ack = b"\x00\x00\x00\x00\x01\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00"

    def bench():
        global ctrl_req, ctrl_addr, ctrl_data, peri1_ack, peri2_ack

        for i in range(len(ctrl_req)):
            yield dut.addr.eq(ctrl_addr[i])
            yield dut.ctrl.req.eq(ctrl_req[i])
            yield dut.ctrl.data.eq(ctrl_data[i])
            yield dut.peri[0xF0].ack.eq(peri0_ack[i])
            yield dut.peri[0xF1].ack.eq(peri1_ack[i])
            yield

    sim = Simulator(dut)
    sim.add_clock(1 / clk_freq_hz)
    sim.add_sync_process(bench)
    with sim.write_vcd(vcd_file=f"{__file__[:-3]}.vcd"):
        sim.run()
