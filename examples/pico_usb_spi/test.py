import serial
import sys

def spi_write(ser, buffer):
    for chunk in [buffer[i:i + 0x7F] for i in range(0, len(buffer), 0x7F)]:
        ser.write(bytes([len(chunk) | (0 << 7)]))
        ser.write(chunk)

def spi_read(ser, length):
    buffer = bytearray()
    while length > 0:
        print(f'read({length})')
        ser.write(bytes([min(0x7F, length) | (1 << 7)]))
        buffer.extend(ser.read(size=min(0x7F, length)))
        length -= 0x7F
    return buffer

def spi_done(ser):
    ser.write(b'\x00')

with serial.Serial(sys.argv[1]) as ser:
    spi_write(ser, bytes([0x9F]))
    print(spi_read(ser, 12))
    spi_done(ser)
