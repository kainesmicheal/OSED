
new_key_gen

while (0x1f < get_lenght_from_user) {

only if the input in less the 31, it will get to next

memset(buff_of_size_40_bytes,0,0x20);

we set 0 to local buffer of size 40, but only 32 bytes (rest of left as it is)

we read random bytes from urandom and write it to the buffer, but we will only wriet 31 bytes

print the buffer

```
strtoul((char *)&local_38,(char **)0x0,0);


0x000055be71e06060 - randbuff
0x00007ffc12f18360 - 40 bytes local buffer

we are setting 0x00 in 32 bytes of the local buffer
we are writing 31 bytes in to the local buffer

we open urandom file and read the number of bytes the user set and copy it to local buffer

we again go through the buffer from index starting from 0 and check if the index == 0x00, if yes, we read 1 bytes again from urandom and copy it to the buffer


copying it back to the randbuf


secure_password

we set 0x17 that is 23bytes of the buffer to zero
actual buffer size is 24
we copy 23 byttes rom flag into the buffer
last byte is probably not set to 0x00

we have local buffer of size 25

we copy the 23 bytes of flag into it

finally we go through all the bytes from 0 to i <= length of stack bufferr

ahd we nor those rand[i] ^ local[i]
```


The strcpy() function copies string2, including the ending null character, 

so we copy 0x00 one at a time to get the full flag

![[Pasted image 20230701101700.png]]