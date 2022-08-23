CXX = c++

all:
	# If you want to rebuild the SDK run "make clean build", but it is
	# not needed. See "include.mk" for using the SDK:
	#	https://pico-ice.readthedocs.io/en/latest/

build: pico-sdk
	make -C pico-sdk/src/rp2_common/boot_stage2 bs2_default_padded_checksummed_asm
	cp -r pico-sdk/src/*/*/include .
	cp -r pico-sdk/generated/pico_base/pico/version.h include/pico
	touch include/pico/config_autogen.h

clean:
	rm -fr pico-sdk include/*/
	rm -f include/pico.h include/tusb_config.h include/cyw43_configport.h

pico-sdk:
	git clone https://github.com/raspberrypi/pico-sdk
	cd pico-sdk && cmake .

elf2uf2:
	$(CXX) -I include -o $@ pico-sdk/tools/elf2uf2/main.cpp
