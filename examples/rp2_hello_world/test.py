from pexpect import fdpexpect
import sys, os

tty = os.open(sys.argv[1], os.O_RDWR)
p = fdpexpect.fdspawn(tty, timeout=1)

print('expect hello world')
p.expect('hello world')

print('done')
p.close()
