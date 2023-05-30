from pexpect import fdpexpect
import sys, os

tty = os.open(sys.argv[1], os.O_RDWR)
p = fdpexpect.fdspawn(tty, timeout=6)

for i in range(0x0, 0x100, 0x20):
    print(f'from 0x{i:X} to 0x{i + 0x20 - 1:X}')
    p.expect(' '.join(f'{n:02X}' for n in range(i, i + 0x20)))

print('done')
p.close()
