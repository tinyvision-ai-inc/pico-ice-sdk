# Pico-Ice Cram Configuration

There are two ways to program the FPGA. A bitstream can be witten to
FLASH and loaded by the FPGA when booting, or the bitstream can be
directly written to the fpga's configuration RAM (cram) by the RP2040 chip.
This SDK example shows how to directly write the bitstream to the cram.

To build the executable, first follow the installation instructions in the root directory and then type:


`cmake .`

This drives a multistage process. In the first stage, a python
program reads in the bitstream and writes out a .h file with the
bitstream data embedded in it.

python3 rgb_blink.py > rgb_blink.h

In the second stage, the new .h file is compiled into an executable found at 

`examples/pico_cram/picoasm/picoasm`

This is an RP2040 executable which can be run on the RP2040 and will
drive the cram initialization process for the FPGA.  Just drag it over to the usb drive, and 
it will install the bitstream on the FPGA.  You will need to do this everytime that you power on the board. 

If you want to install a different bitstream on the FPGA, just overwrite `rgb_blink.bin` with your bitstream and rerun

`cmake .`

## TODO

Pasa an argument to the cmake file with the name of the bitstream to be used. 
