Important change is Source -> Destination

mov %esp, %ebp - which in intel will be - mov ebp, esp

registers get a prefix of % eg; %esp

immediates get a $ eg: add $0x10, %esp

![[Pasted image 20210802033118.png]]

the mnemonic will have an indicator of the size

movb - operates on bytes
mov/movw - operates on word (2bytes)
movl - operates on long (4bytes)

intel does it like mov dword ptr [eax]

to compile with debug options in linux gcc

gcc -ggdb -o outname filename.c

objdump can be used for disassembly

objdump -d filename

to change the output sytnax to intel

objdump -d filename -M intel

xxd -d filename -> to get hex dump
xxd -r modifiedhexdump -> converted the hexdump into executable

