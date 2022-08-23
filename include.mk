# This file is to be included from your project's Makefile like this:
#
#	PICO_ICE_OBJ = your-firmware.o your-source.o
#	PICO_ICE_SDK = path/to/pico-ice-sdk
#	include $(PICO_ICE_SDK)/include.mk

ELF2UF2 = $(PICO_ICE_SDK)/elf2uf2
OBJCOPY = arm-none-eabi-objcopy
OBJDUMP = arm-none-eabi-objdump
CC = arm-none-eabi-gcc -mthumb -mcpu=cortex-m0plus -msoft-float
LD = arm-none-eabi-ld
PICO_ICE_LDFLAGS = -Map=firmware.map --gc-sections -T$(PICO_ICE_SDK)/script.ld -nostdlib
PICO_ICE_CFLAGS = -I$(PICO_ICE_SDK)/include -ffunction-sections -fdata-sections
PICO_ICE_LIB = \
$(PICO_ICE_SDK)/src/init.o \
$(PICO_ICE_SDK)/src/gpio.o \
$(PICO_ICE_SDK)/src/spi.o \
$(PICO_ICE_SDK)/src/libc.o

firmware.uf2: firmware.elf $(ELF2UF2)
	$(ELF2UF2) firmware.elf $@

firmware.elf: $(PICO_ICE_OBJ) $(PICO_ICE_LIB)
	$(LD) $(PICO_ICE_LDFLAGS) $(LDFLAGS) -o $@ $(PICO_ICE_OBJ) $(PICO_ICE_LIB)
	$(OBJDUMP) -z -d $@ >firmware.asm

clean:
	rm -f $(PICO_ICE_OBJ) *.o *.map *.asm *.elf *.uf2

$(ELF2UF2):
	make -C $(PICO_ICE_SDK) elf2uf2

.SUFFIXES: .S .c .o

.S.o:
	$(CC) $(PICO_ICE_CFLAGS) $(CFLAGS) -c -o $@ $<

.c.o:
	$(CC) $(PICO_ICE_CFLAGS) $(CFLAGS) -c -o $@ $<
