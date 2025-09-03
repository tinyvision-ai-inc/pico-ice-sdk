YOSYS = $(OSS_CAD_SUITE)/bin/yosys
NEXTPNR = $(OSS_CAD_SUITE)/bin/nextpnr-ice40
ICEPACK = $(OSS_CAD_SUITE)/bin/icepack
DFU_UTIL = $(OSS_CAD_SUITE)/bin/dfu-util
BIN2UF2 = bin2uf2

VERILATOR = $(OSS_CAD_SUITE)/bin/verilator
VERILATOR_INC = $(OSS_CAD_SUITE)/share/verilator/include
VERILATOR_SRC = $(VERILATOR_INC)/verilated.cpp $(VERILATOR_INC)/verilated_vcd_c.cpp $(VERILATOR_INC)/verilated_threads.cpp
CXX = c++ -I$(VERILATOR_INC) #-DNDEBUG

DFU_ALT_FLASH = 0
DFU_ALT_CRAM = 1

RTL = top.sv

all: gateware.bin verilator.vcd

clean:
	$(RM) -r obj_dir *.json *.asc *.bin *.uf2 *.elf

prog: gateware.bin
	$(DFU_UTIL) -d 1209:b1c0 -a $(DFU_ALT_FLASH) -D gateware.bin -R

gateware.bin: ice40.sv $(RTL)
	$(YOSYS) -q -p "read_verilog -sv ice40.sv $(RTL); synth_ice40 -top ice40 -json $*.json"
	$(NEXTPNR) -q --randomize-seed --up5k --package sg48 --pcf ice40.pcf --json $*.json --asc $*.asc
	$(ICEPACK) $*.asc $@

verilator.vcd: verilator.cpp vsim.h $(RTL)
	$(VERILATOR) -Wall -DSIMULATION -Irtl --trace --sv --trace-structs --cc --top-module top $(RTL)
	$(MAKE) -C obj_dir -f Vtop.mk
	$(CXX) -Iobj_dir -o verilator.elf $(VERILATOR_SRC) verilator.cpp obj_dir/Vtop__ALL.a
	./verilator.elf >$@

.bin.uf2:
	$(BIN2UF2) -o $@ $<

.SUFFIXES: .v .sv .vcd .bin .uf2
