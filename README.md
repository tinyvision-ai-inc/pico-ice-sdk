# pico-ice-sdk
The firmware library for the [pico-ice](https://pico-ice.readthedocs.io/),
a board combining a Raspberry Pi RP2040 and an Lattice iCE40.

You can download it somewhere then source `include.mk` from your project.
Make sure `include` is after `PICO_ICE_OBJ` as below:

```
PICO_ICE_OBJ = your-firmware.o your-source.o
PICO_ICE_SDK = path/to/pico-ice-sdk
include $(PICO_ICE_SDK)/include.mk
```

You can also set `CFLAGS` and `LDFLAGS` anywhere in your Makefile to
add extra flags to compile with:

```
CFLAGS = -Wall -Wextra -std=c99 -pedantic
```

See the complete documentation at https://pico-ice.readthedocs.io/
