YOSYS = yosys
NEXTPNR = nextpnr-ice40
ICEPACK = icepack
BIN2UF2 = bin2uf2
DFU_UTIL = dfu-util

RTL = top.v

all: gateware.bin

clean:
	$(RM) *.json *.asc *.bin *.uf2

prog: gateware.bin
	$(DFU_UTIL) -d 1209:b1c0 -a 1 -D gateware.bin -R

gateware.json: $(RTL)
	$(YOSYS) -q -p "read_verilog -sv $(RTL); synth_ice40 -top top -json $@"

.json.asc:
	$(NEXTPNR) -q --randomize-seed --up5k --package sg48 --pcf up5k.pcf --json $< --asc $@

.asc.bin:
	$(ICEPACK) $< $@

.bin.uf2:
	$(BIN2UF2) -o $@ $<

.SUFFIXES: .v .sv .json .asc .bin .uf2
