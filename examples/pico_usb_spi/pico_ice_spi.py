import serial
import sys

class PicoIceSpi:
    USE_FPGA = 0x00
    USE_SRAM = 0x01
    USE_FLASH = 0x02

    def __init__(self, port):
        self.ser = serial.Serial(port)

    def write(self, buffer):
        for chunk in [buffer[i:i + 0x7F] for i in range(0, len(buffer), 0x7F)]:
            self.ser.write(bytes([len(chunk) | (0 << 7)]))
            self.ser.write(chunk)

    def read(self, length):
        buffer = bytearray()
        while length > 0:
            self.ser.write(bytes([min(0x7F, length) | (1 << 7)]))
            buffer.extend(self.ser.read(size=min(0x7F, length)))
            length -= 0x7F
        return buffer

    def done(self):
        self.ser.write(b'\x00')

    def command(self, byte):
        self.ser.write([0x80, byte])
