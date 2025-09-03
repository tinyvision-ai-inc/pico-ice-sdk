YOSYS = $(OSS_CAD_SUITE)/bin/yosys
NEXTPNR = $(OSS_CAD_SUITE)/bin/nextpnr-ice40
ICEPACK = $(OSS_CAD_SUITE)/bin/icepack
DFU_UTIL = $(OSS_CAD_SUITE)/bin/dfu-util
BIN2UF2 = bin2uf2

IVERILOG = $(OSS_CAD_SUITE)/bin/iverilog
VVP = $(OSS_CAD_SUITE)/bin/vvp

DFU_ALT_FLASH = 0
DFU_ALT_CRAM = 1

RTL = top.sv

all: gateware.bin iverilog.vcd

clean:
	$(RM) -r obj_dir *.json *.asc *.bin *.uf2 *.elf

prog: gateware.bin
	$(DFU_UTIL) -d 1209:b1c0 -a $(DFU_ALT_FLASH) -D gateware.bin -R

gateware.bin: ice40.sv $(RTL)
	$(YOSYS) -q -p "read_verilog -sv ice40.sv $(RTL); synth_ice40 -top ice40 -json $*.json"
	$(NEXTPNR) -q --randomize-seed --up5k --package sg48 --pcf ice40.pcf --json $*.json --asc $*.asc
	$(ICEPACK) $*.asc $@

iverilog.vcd: testbench.sv $(RTL)
	$(IVERILOG) -g2012 -Wall -o $*.vvp testbench.sv $(RTL)
	$(VVP)  $*.vvp $@

.bin.uf2:
	$(BIN2UF2) -o $@ $<

.SUFFIXES: .v .sv .vcd .bin .uf2
