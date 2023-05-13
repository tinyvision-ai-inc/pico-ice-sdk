# python
from enum import IntEnum

# amaranth
from amaranth import *
from amaranth.sim import *

# local
from spi import *
from handshake import *


__all__ = [ "Spibone" ]


class Spibone(Elaboratable):
    def __init__(self):
        # Upstream SPI interface
        self.rx = HandshakePeriInInterface(width=8)
        self.tx = HandshakeCtrlOutInterface(width=8)

        # Downstream bus interface
        self.addr = Signal(32)
        self.rbus = HandshakeCtrlInInterface(width=32)
        self.wbus = HandshakeCtrlOutInterface(width=32)

    def elaborate(self, platform):
        m = Module()

        cmd = Signal(8)
        CMD_WRITE = 0x00
        CMD_READ = 0x01

        addr = Signal(32)
        rdata = Signal(32)
        wdata = Signal(32)

        with m.FSM():

            with m.State("IDLE"):
                with m.If(self.rx.req):
                    m.d.comb += self.rx.ack.eq(1)

                    with m.If((self.rx.data == CMD_READ) | (self.rx.data == CMD_WRITE)):
                        m.d.sync += cmd.eq(self.rx.data)
                        m.next = "GET_ADDR0"

            for i in range(4):
                with m.State(f"GET_ADDR{i}"):
                    with m.If(self.rx.req):
                        m.d.comb += self.rx.ack.eq(1)
                        m.d.sync += addr.eq(Cat(addr[0:-8], self.rx.data))

                        if i + 1 < 4:
                            m.next = f"GET_ADDR{i + 1}"
                        else:
                            with m.If(cmd == CMD_READ):
                                m.next = "READ_BUS_REQUEST"
                            with m.If(cmd == CMD_WRITE):
                                m.next = "WRITE_GET_DATA0"

            # Write command

            for i in range(4):
                with m.State(f"WRITE_GET_DATA{i}"):
                    with m.If(self.rx.req):
                        m.d.comb += self.rx.ack.eq(1)
                        m.d.sync += wdata.eq(Cat(self.rx.data, wdata[0:-8]))
                        if i + 1 < 4:
                            m.next = f"WRITE_GET_DATA{i + 1}"
                        else:
                            m.next = f"WRITE_BUS_REQUEST"

            with m.State(f"WRITE_BUS_REQUEST"):
                self.bus_write(m, addr, wdata)
                with m.If(self.wbus.ack):
                    m.next = "WRITE_PUT_ACK"

            with m.State(f"WRITE_PUT_ACK"):
                self.tx.write(m, CMD_WRITE)
                with m.If(self.tx.ack):
                    m.next = "IDLE"

            # Read command

            with m.State(f"READ_BUS_REQUEST"):
                self.bus_read(m, addr, rdata)
                with m.If(self.rbus.ack):
                    m.next = "READ_PUT_ACK"

            with m.State("READ_PUT_ACK"):
                self.tx.write(m, CMD_READ)
                with m.If(self.tx.ack):
                    m.next = "READ_PUT_DATA0"

            for i in range(4):
                with m.State(f"READ_PUT_DATA{i}"):
                    self.tx.write(m, rdata[-8:])
                    with m.If(self.tx.ack):
                        if i + 1 < 4:
                            m.next = f"READ_PUT_DATA{i + 1}"
                        else:
                            m.next = "IDLE"
                        m.d.sync += rdata.eq(Cat(rdata[0:-8], 0x00))

        return m

    def bus_read(self, m, addr, data):
        m.d.comb += self.addr.eq(addr)
        self.rbus.read(m, data)

    def bus_write(self, m, addr, data):
        m.d.comb += self.addr.eq(addr),
        self.wbus.write(m, data),

if __name__ == "__main__":
    dut = Spibone()

    dut.tx.connect(HandshakeCtrlOutInterface(width=8))
    dut.rx.connect(HandshakePeriInInterface(width=8))
    dut.rbus.connect(HandshakePeriOutInterface(width=32))
    dut.wbus.connect(HandshakePeriInInterface(width=32))

    clk_freq_hz = 10e6 # MHz

    # Write request

    rx_req      = b"\x00\x01\x00\x01\x01\x01\x00\x01\x01\x01\x01\x00\x01\x00\x00\x00\x00"
    rx_data     = b"\x00\x00\x00\xF0\xF0\xF0\x00\xF0\x12\x34\x56\x00\x78\x00\x00\x00\x00"
    tx_ack      = b"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00"
    #                    WWW     AAA AAA AAA AAA     DDD DDD DDD     DDD                
    rbus_ack    = b"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
    rbus_data   = b"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
    wbus_ack    = b"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00"

    # Read request                                                              

    rx_req      += b"\x00\x01\x00\x01\x01\x01\x00\x01\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
    rx_data     += b"\x00\x01\x00\xF1\xF1\xF1\x00\xF1\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
    tx_ack      += b"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x01\x01\x01\x01\x01\x00"
    #                    RRR     AAA AAA AAA     AAA                                     
    rbus_ack    += b"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x00\x00\x00\x00\x00"
    rbus_data   += b"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x55\x00\x00\x00\x00\x00\x00\x00"
    wbus_ack    += b"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"

    def bench():
        global rx_req, rx_data, reader_ack, writer_ack, writer_data

        for i in range(len(rx_req)):
            yield dut.rx.req.eq(rx_req[i])
            yield dut.rx.data.eq(rx_data[i])
            yield dut.tx.ack.eq(tx_ack[i])
            yield dut.wbus.ack.eq(wbus_ack[i])
            yield dut.rbus.data.eq(rbus_data[i])
            yield dut.rbus.ack.eq(rbus_ack[i])
            yield

    sim = Simulator(dut)
    sim.add_clock(1 / clk_freq_hz)
    sim.add_sync_process(bench)
    with sim.write_vcd(vcd_file=f"{__file__[:-3]}.vcd"):
        sim.run()

