signed integers, means they can have negtive value

eg vulnerable code:

```
int test_function(struct socket *sock, int proto) 
{
	if (proto >= 5) return INVALID;

	return sock[proto]->create(sock.value);
}
```

in this case, as we only check for the upper limit of the proto to not read outside the buffer

int acan also hold negative value, that would cause it access negative index causing crash

NULL pointer dereference

C standard NULL pointer = 0x00

if a kernel path attempts to dereference a NULL pointer, it will simply try to use the memory address 0x000, as nothing is mapped that address, it wll panic

This comes under a category

-> while its context has been corrupted
-> was never properly set
-> not validated enough

as pointer itself has to be stored, it takes the same space as the arch bit size

64-bit arch has pointer size of 64

if we declare a pointer and not initialize it, the value of the pointer will be the gragabe random value that was left in the place

```
#include <stdio.h>
#include <string.h>

void random_stack() {
        char value[200];
        memset(value, 'A', 200);
        value[200] = '\0';
        printf("Random stack %s\n", value);
}

void un_initialized_pointer() {
        char *ptr;
        char val[100];
        printf("Uninitialized Pointer value: %p\n", ptr);
}

int main() {
        random_stack();
        un_initialized_pointer();
}
```

because my ptr is unintialized, the compiler does the trick to add something valid address to it. (my compiler gcc (Debian 11.3.0-1) 11.3.0)

![[Pasted image 20220806083405.png]]

![[Pasted image 20220806083215.png]]


Non validated pointer

in combined user and kernel address space

some virtual address is chosen as the limit address, this means the virtual address above it belong to the kernel and virtual address belore it belong to the user process

The internal kernel functions use this address to decide if a specifi pointer points to kernel land or user land

linux function starts with __ doesnt perform any checks on the supplied destination or source user land pointer


an arbitary read occurs when the kernel attempts to read from the trashed pointer

An arbitary write occurs when the kernel attempts to store a value on the memory address referened by the pointer

uncontrolled read/write occurs when the attacker has no control over the value of the trashed pointer




