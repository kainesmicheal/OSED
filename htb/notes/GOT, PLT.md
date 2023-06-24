

Each ELF will not carry their own version of puts compiled within it, it will be dynamically link to the puts of the system it is on.

so does all of those functions have a hardcoded addresses?

nope,

the problem with hardcoding the address, is the libc have to be loaded in constant base address, as we have ASLR, it will be loaded in different base address every time, so we need to fetch that address dynamically


The PLT (Procedure Linkage Table) and GOT (Global Offset Table) work together to perform the linking

for example when we call printf, it is not actually printf, instead it gets compiled as printf@plt

![[Pasted image 20230624024454.png]]

we dont know where printf is

we jump to printf@plt

this plt functions do two things

- if there is a GOT entry for puts, it jumps to the address stored there.
- if there isn't a GOT entry, it wll resolve it and jump there

The GOT is a massive table of address, these address are actual locations in memory of the libc functions, printf@got

printf@plt will read GOT address and redirect execution there

