from pexpect import fdpexpect
import sys, os

FF = 'FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF'
OO = '00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00'

tty = os.open(sys.argv[1], os.O_RDWR)
p = fdpexpect.fdspawn(tty, timeout=1)

print('resetting position')
p.sendline('0x00000000')
p.expect('0x00000000>')

print('erase command')
p.sendline('e')
p.expect('repl_command_erase 0x00000000 done')
p.expect('0x00000000>')

print('read command')
p.sendline('r')
p.expect('repl_command_read 0x00000000 done')
p.expect(f'0x00000000: {FF}')
p.expect(f'0x00000020: {FF}')
p.expect(f'0x00000040: {FF}')
p.expect(f'0x00000060: {FF}')
p.expect(f'0x00000080: {FF}')
p.expect(f'0x000000A0: {FF}')
p.expect(f'0x000000C0: {FF}')
p.expect(f'0x000000E0: {FF}')

print('zero command')
p.sendline('z')
p.expect('repl_command_zero 0x00000000 done')
p.expect('0x00000000>')

print('read command')
p.sendline('r')
p.expect('repl_command_read 0x00000000 done')
p.expect(f'0x00000000: {OO}')
p.expect(f'0x00000020: {OO}')
p.expect(f'0x00000040: {OO}')
p.expect(f'0x00000060: {OO}')
p.expect(f'0x00000080: {OO}')
p.expect(f'0x000000A0: {OO}')
p.expect(f'0x000000C0: {OO}')
p.expect(f'0x000000E0: {OO}')

print('done')
p.close()
