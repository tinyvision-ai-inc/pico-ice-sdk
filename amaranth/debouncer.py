# amaranth
from amaranth import *


__all__ = [ "Debouncer" ]


class Debouncer(Elaboratable):
    """
    Debounce a signal by rejecting jitter.
    """

    def __init__(self, *, width):
        self.width = width

        self.i = Signal(1)
        self.o = Signal(1)

    def elaborate(self, platform):
        m = Module()
        buffer = Signal(self.width)

        m.d.sync += buffer.eq(Cat(self.i, buffer))

        with m.If(buffer.any() == 0):
            m.d.sync += self.o.eq(0)

        with m.If(buffer.all() == 1):
            m.d.sync += self.o.eq(1)

        return m
