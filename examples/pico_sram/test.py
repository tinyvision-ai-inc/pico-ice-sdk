from pexpect import fdpexpect
import sys, os

tty = os.open(sys.argv[1], os.O_RDWR)
p = fdpexpect.fdspawn(tty, timeout=1)

print('expect Chip ID')
p.expect('0x0D5D5AB1C0219DB2')

print('done')
p.close()
