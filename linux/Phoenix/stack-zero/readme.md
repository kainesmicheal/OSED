we there is struct in the stack, it holds a buffer size of 64 bytes,

we can write to that buffer using gets

next to the buffer, we have variable named changeme

65byte will be the memory location of changeme variable

we can overflow the buffer with 65 bytes

python3 -c 'print("B"*65)' | ./program
