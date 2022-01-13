The 64-bit versions, registers are named:

rax — register a extended
rbx — register b extended
rcx — register c extended
rdx — register d extended
rbp — register base pointer
rsp — register stack pointer
rsi — register source index
rdi — register destination index

Arguments to functions in x64 are passed in registers RDI, RSI, RDX, R10, R8, and R9, With the first argument in RDI. We’re investigating the x64 binary, we can see that we ought to pass our single argument to system() within the RDI register.