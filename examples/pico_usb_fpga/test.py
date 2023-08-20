import pexpect
import sys, os

FF = 'FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF'
OO = '00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00'

p = pexpect.spawn("dfu-util -l", timeout=1)

print('expecting two interfaces from dfu-util')
p.expect('1209:b1c0')
p.expect('1209:b1c0')

print('done')
