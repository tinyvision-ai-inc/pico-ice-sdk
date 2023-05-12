# python
from enum import IntEnum

# amaranth
from amaranth import *

# local
from spi import *
from handshake import *


__all__ = [ "Spibone" ]


class Spibone(Elaboratable):
    def __init__(self, addr=32, data=32):
        self.spi = SpiPeriInterface()

    def add_reader(self, addr, peri)
        self.rbus.add_peri(addr, peri)

    def add_writer(self, addr, peri)
        self.wbus.add_peri(addr, peri)

    def elaborate(self):
        m = Module()

        m.submodules.rbus = rbus = HandshakeInterconnect(addr=addr, data=data)
        m.submodules.wbus = wbus = HandshakeInterconnect(addr=addr, data=data)

        cmd = Signal(8)
        CMD_READ = 0x00
        CMD_WRITE = 0x01

        addr = Signal(4)
        data = Signal(4)

        with m.FSM():

            with m.State("IDLE"):
                with m.If(self.spi.rx.req):
                    m.d.comb += m.spi.rx.ack.eq(1)

                    m.d.sync += cmd.eq(self.spi.rx.data)

                    with m.If(self.spi.rx.data in (Command.READ, Command.WRITE)):
                        m.d.comb += cmd.eq(self.spi.rx.data)
                        m.next = "GET_ADDR0"

            for i in range(4):
                with m.State(f"GET_ADDR{i}"):
                    with m.If(self.spi.rx.req):
                        m.d.comb += m.spi.rx.ack.eq(1)

                        slice = addr[i * 8 : (i + 1) * 8]
                        m.d.sync += slice.eq(self.spi.rx.data)

                        if (i + 1 < 4):
                            m.next = f"GET_ADDR{i + 1}"
                        else:
                            with m.If(cmd == CMD_READ):
                                m.next = "READ_BUS_REQUEST"
                            with m.If(cmd == CMD_WRITE):
                                m.next = "WRITE_GET_DATA0"

            # Write command

            for i in range(4):
                with m.State(f"WRITE_GET_DATA{i}")
                    with m.If(self.spi.rx.req):
                        m.d.comb += m.spi.rx.ack.eq(1)

                        slice = data[i * 8 : (i + 1) * 8]
                        m.d.sync += slice.eq(self.spi.rx.data)

                        if (i + 1 < 4):
                            m.next = f"{WRITE_GET_DATA{i + 1}"
                        else:
                            m.next = f"{WRITE_BUS_REQUEST}"

            with m.State(f"WRITE_BUS_REQUEST"):
                m.d.comb += wbus.write(addr, data)
                with m.If(wbus.ack)
                    m.next = "WRITE_PUT_ACK"

            with m.State(f"WRITE_PUT_ACK")
                m.d.comb += self.spi.write(CMD_WRITE)
                with m.If(self.spi.tx.ack)
                    m.next = "IDLE"

            # Read command

            with m.State(f"READ_BUS_REQUEST"):
                m.d.comb += rbus.addr.eq(addr)
                m.d.comb += rbus.read(data)
                with m.If(rbus.ack)
                    m.next = "READ_PUT_ACK"

            with m.State("READ_PUT_ACK"):
                    m.d.comb += self.spi.write(CMD_READ)
                    m.d.comb += rbus.addr

                    m.next = "READ_PUT_DATA0"

            for i in range(4):
                with m.State(f"READ_PUT_DATA{i}"):
                    slice = data[i * 8 : (i + 1) * 8]
                    m.d.comb += self.spi.write(slice)
                    with m.If(self.spi.ack):
                        if (i + 1 < 4):
                            m.next = f"READ_PUT_DATA{i + 1}"
                        else:
                            m.next = "IDLE"

        return m
