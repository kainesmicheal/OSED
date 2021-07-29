##Naming convention in intel x86

![[Pasted image 20210728123656.png]]

c naming : size : intel naming

char [C(7,0)] Byte

short [High Byte(15,8), Low Byte(7,0)] Word

int/long [High Word(31,16), Low Word(15,0)] Doubleword

double/long long [High Doubleword(63,32), Low Doubleword(31,0)] Quadword

Decimal, Binary, Hexadecimal 

![[Pasted image 20210728124456.png]]

4-bits is called a nibble

8-bits is called a byte

a single hex decimal char (0x05) is essentially a nibble

in a binary number, the bit furthest to the left is called the most significant bit(msb) and the bit furthest to the right is called the least significant bit(lsb).

msb
|
10010010
               |
			   lsb
![[Pasted image 20210728135700.png]]

##Negative Numbers:
	They are the two's compliment of the positive number
	
	1's compliment is just flip all the bits
	2's compliment is add 1 to 1's complement
	
	00000001 -> 11111110 -> 11111111
	
![[Pasted image 20210728130407.png]]
	
##Architecure - CISC vs RISC

CISC - Complex Instruction Set 
	It keeps on adding new instructions to run a block of code that was found to used more frequently.
	eg: intel x86
	
RISC - Reduced Instruction Set 
	Typically more registers, less and fixed size instructions
	eg: ARM, PowerPC

##ENDIANNESS
	There is no functional change just they way its is represented differs
	
	Little Endian: The least significant byte of a word id stored in the lowest address, Intel is little Endian
		eg: 0x12345678 will be stored as 0x78563412
	
	Big Endian: its just goes as it is directly, arm is big endian
		eg: 0x12345678 will be stored as 0x 12345678
		
	Bi-Endian: can be configured to any either way

##Registers:
	small memory storage areas built into the processor (volatile memory)
	8 general purpose registers + the instruction pointer (EIP)
	
	in x86-32, registers are 32 bits long
	
	EAX - Stores function return values, it can also be used as accumulator
	EBX - Base pointer to the data section
	ECX - Counter for string and loop operations
	EDX - I/O pointer
	ESI - Source pointer
	EDI - Destination pointer
	ESP - Stack pointer
	EBP - Stack Frame base pointer
	EIP - pointer to next instruction to execute (instruction pointer)
	

##Registers Conventions:

	Caller-save: eax, edx, ecx
		if the caller has anything in the registers that it cares about the caller is in charge of saving the values before a call to a subroutine, and restoring the values after the call returns.
		
	Callee-save: ebp, ebx, esi, edi
		if the calle need to use more registers that are saved by the caller, the calle is responsible for making sure the values are stored/restored
		

Different portions of a register could be accessed and modified as need

[31,0] -> EAX
[15,0] -> AX
[15,7] -> AH
[0,7] -> AL

![[Pasted image 20210728134458.png]]
![[Pasted image 20210728134837.png]]

EFLAGS is a special register that hold many bit flags

each bit in this register holds a special purpose

zero flag(ZF) - Set if the result of some instruction is zero 
Sign flag(SF) - Set equal to the most significant bit of the result, which is the sign bit of a signed interger. (as all negative numbers start with 1 and all positive number start with 1)

##STACK
	-> it is a last in first out data structure where data is "pushed" on to the top of the stack and "popped" off the top
	-> By convention the stack grows towards the lower memory addresses
	-> OS allocates stack space in ram for every program when it is started
	-> ESP points to the top of the stack
	-> every function get its own stack, which is maintained by the stack frame
	
##Calling Conventions
	there are many such conventions, most common are
		-> cdecl (C declaration)
		-> stdcall (standard call)
	cdecl:
		-> Function parameters pushed onto stack right to left
		-> Saves old stack frame pointer and sets up a new stack frame
		-> the return value are stored in eax (if 32 bit value), eax:edx (if 64 bit value)
		-> Caller is responsible for cleaning up the stack, that is to pop of the paramater that are pushed on to the stack, when the function was called
	stdcall:
		-> Called function is responsible for cleaning up stack by poping the parameters what were passed to it.
	
	Only difference between cdecl and stdcall is "who does the cleanup of the parameter pushed in the stack?"
	
	stdcall is used in the win32 API
	
##General Stack Frame Operation

when a function needs to be called, the caller will 
	-> save the registers that might be needed later by pushing them on to the stack
	-> push the parameters needed for the funtion (right to left)
	-> call instruction will push the address of next instruction on to the stack (for returning) and jump to the address of the function that we wana call
	-> now the called funtion will push the current stack base pointer to the stack
	-> set its own stack base pointer to the current esp (so the saved frame pointer is where the new stack frame starts for the called function)
	
```
push ebp ;pushing the current stack frame pointer to the stack
move ebp, esp ;move address of esp to ebp
```

```
; before return 
mov esp, ebp ; aligns the stack pointer back to top of the stack fram
pop ebp ; pop top of the stack which is the saved stack pointer into ebp
ret ; return
```

Debugger using the ebp tracking to get the call stack, as by looking at the saved stack pointer and the saved return address, debugger is able to produce the call stack for us.

##Addressing Forms:
		
		in intex syntax most of the time square brackets [] means to treat the value within as a memory address and fetch the value at the address
		
		LEA is a exception that wont do that
		
![[Pasted image 20210729132237.png]]
	
		array can accessed using this method [ base + index * scale + disp ]
		do the calculation and treat the result of the calculation as memeory address
		
		where,
				base = base address of the array
				index = offset into the array
				scale = if the value stored is also an arrray, scale is the length of the second array
				disp  = is the index in the second arraay
	
##Instructions:

	NOP :
		-> No operations
		-> for padding memory or alignment
		-> it actually does a  
				XCHG EAX, EAX 
			which literally takes whatever is in EAX and puts it back in EAX
	PUSH:
		-> pushes the value on top of the stack and decrements the stack pointer (ESP) by 4 bytes
		-> eg: PUSH EAX - this puts whatever in eax into top of the stack and decrements the esp by 4 bytes
	POP:
		-> removes the value on top of the stack and puts that into the given register and increments the stack pointer by 4 bytes
		-> eg: POP EAX - this puts whatever in the top of the stack into eax register and incerments the esp by 4 bytes
	CALL:
		-> it pushes the address of the next instruction onto the stack
		-> then it changes the eip to the address given in the instruction
		-> address can be absolute or relative
		-> eg: CALL 0xdeadbeef - pushes the address of next instruction into stack and puts 0xdeadbeef into eip
	RET:
		-> Pop the top of the stack into eip (POP increments stack pointer)
		-> if you provide a byte to ret, it will that to the esp
		-> RET 0x4 - pop the top of the stack to EIP, increment ESP + 4 bytes
	MOV:
		-> can move register to register, memory to register, register to memory, immediate to register, immediate to memory.
		-> Never from memory to memory
		-> MOV EAX, 0x12345678 - move 0x12345678 into EAX
	LEA:
		-> used for pointer aithmetic or general arthimetic
		-> lea eax, [edx + ebx *2], this takes value or edx + value of ebx * 2 and puts that into eax, this wont dereference the result of the calculation, it wont go into the address to just will take the address literally and do the calculations.
	
		
	 
		










		




