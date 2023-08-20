from pico_ice_spi import *
import binascii

# Open the port given as argument
spi = PicoIceSpi(sys.argv[1])

# Query the SRAM ID
spi.command(spi.USE_SRAM)
spi.write(b'\x9F\x00\x00\x00')
id = spi.read(8)
print('SRAM ID: ' + str(binascii.b2a_hex(id, ' ')))
spi.done()

# Query the FLASH ID
spi.command(spi.USE_FLASH)
spi.write(bytes(b'\xAB\x00\x00\x00'))
id = spi.read(1)
print('FLASH ID: ' + str(binascii.b2a_hex(id, ' ')))
spi.done()
