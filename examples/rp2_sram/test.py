from pexpect import fdpexpect
import sys, os

tty = os.open(sys.argv[1], os.O_RDWR)
p = fdpexpect.fdspawn(tty, timeout=1)

print('expect Chip ID')
p.expect('ChipID: 0D 5D 5A B1 C0 21 9D B2')

print('expect memory data')
p.expect('0x0000: 01 02 03 04 05 06 07 08')

print('done')
p.close()
