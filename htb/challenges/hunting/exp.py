from pwn import *

context.arch = "amd64"

r = gdb.debug("./hunting")

r.send(0xdeadbeeff)
r.recv()
