buffer is at address 0x00007fffffffdc60
0x00007fffffffdc9c afte intial greet message
ret address is at 0x00007fffffffdd08

we need to write 168 bytes to overwrite that return address

greet message should 50 - 60 bytes

then because the buffer is added to the banner size and maxsize is copied from that location, we can overwrite the ret address

exp=$(python3 -c "print('B'*100+'C'*16)") gdb ./program

jump to 0x7fffffffdcf0
