CXX = c++

all:
	# see include.mk and https://pico-ice.readthedocs.io/

build: pico-sdk
	cp src/pico-ice.h include

clean:
	rm -fr pico-sdk cmsis-5 include

pico-sdk:
	git clone https://github.com/raspberrypi/pico-sdk
	cd pico-sdk && cmake .
	cp -r pico-sdk/src/*/*/include .
	cp -r pico-sdk/generated/pico_base/pico/version.h include/pico
	touch include/pico/config_autogen.h

elf2uf2:
	$(CXX) -I include -o $@ pico-sdk/tools/elf2uf2/main.cpp
