from pwn import process, p32, gdb, pause

# p = process("./example1")
# p.interactive()

# p = process("./example1")
# recv1 = p.recvline()

# print(recv1)

# send1 = b"Micheal"
# send1 = p32(0xdeadbeef)

# p.sendline(send1)

# recv2 = p.recvline()

# print(recv2)

## with gdb

p = gdb.debug("./example1", '''
continue
''')
recv1 = p.recvline()

print(recv1)

send1 = b"Micheal"
send1 = p32(0xdeadbeef)

p.sendline(send1)

pause()

recv2 = p.recvline()

print(recv2)
