print('#include <stdint.h>')
print('uint8_t const rgb_blink[] = {')

i = 0
for byte in open('rgb_blink.bin', 'rb').read():
    if i == 0:
        print('   ', end='')
    print(' 0x%02X,' % byte, end='')
    i += 1
    if i == 16:
        print('')
        i = 0
if i != 1:
    print('')
print('};')
