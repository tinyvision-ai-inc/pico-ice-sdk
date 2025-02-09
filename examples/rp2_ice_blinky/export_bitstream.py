#! /usr/bin/env python3
print(', '.join(map(hex, open('bitstream.bin', 'rb').read())))
