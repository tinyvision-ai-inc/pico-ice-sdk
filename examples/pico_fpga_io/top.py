import sys, os
sys.path.append(os.path.dirname(__file__) + "/pico-ice-sdk/amaranth")

# amaranth
from amaranth import *
from amaranth.build import *
from amaranth.cli import main
from amaranth_boards.resources import *

# pico-ice-sdk
from pico_ice import *

class Top(Elaboratable)
    def elaborate(self, platform):
        m = Module()
        fpga = platform.request("fpga", 0)

        #

        return m

if __name__ == "__main__":
    platform = PicoIcePlatform()
    platform.build(TopLevel, do_program=True, program_opts={"dfu_alt": 1})

