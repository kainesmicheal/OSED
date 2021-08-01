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

```

#you can directly add  __stdcall infront of a function to make it used stdcall instead of cdecl

int __stdcall sub(int x, int y)

```

##Addressing Forms:

		in intex syntax most of the time square brackets [] means to treat the value within as a memory address and fetch the value at the address
		
		LEA is a exception that wont do that
		
		example:
		
			ecx = 0x00C436B0
			eax = 0x00000004
		
			mov edx, [ecx+eax]
			
			take the value of ecx and eax
			
			it will be like [0x00C436B0 + 0x00000004]
								=>			[0x00C436B4]
			now dereference this address or go to the address and take the value in it which is
![[Pasted image 20210730051743.png]]
			
			0x00C436B4 =  00c43745
			
			move 00c43745 into edx
			
		
![[Pasted image 20210729132237.png]]
	
		array can accessed using this method [ base + index * scale + disp ]
		do the calculation and treat the result of the calculation as memeory address
		
		where,
				base = base address of the array
				index = offset into the array
				scale = if the value stored is also an arrray, scale is the length of the second array
				disp  = is the index in the second arraay
				
##tips:
	
		ebp + somthing -> paramters passwd to the function
		ebp - something -> mostly local varibles that are pushed on to the stack, if they where are allocated.

##Control Flow
	
	Two forms of control flow
	
	- Conditional - go somewhere if a condition is met. if, switch, loops
	- Unconditional - go somewhere no matter what. procedure calls, goto, exceptions, intreupts
	
##bit wise arithmetic 

![[Pasted image 20210730145146.png]]

##bit shifting:
	
	every bit is power of two starting from right increasing
	
	00001010 	=> 0 * 2^0
						   => 1 * 2^1
						   => 0 * 2^2
						   => 1 * 2^3
						   => 0 * 2^4
						   => 0 * 2^5
						   => 0 * 2^6
						   => 0 * 2^7
						  	__________
							total =	10
		if we shit this be left 00001010 will be 00010100
		
			00010100 	=> 0 * 2^0
						   		   => 0 * 2^1
						 		   => 1 * 2^2
						   			=> 0 * 2^3
						   			=> 1 * 2^4
						   			=> 0 * 2^5
						   			=> 0 * 2^6
						   			=> 0 * 2^7
						  			__________
									total =	20
									
		if the number is a power of two (2) it can be easily divided or multiplying just by using right and left shit
									
		this also means the shit to left effectively muliptles by 2
		
		and shiting to right efectively divided by 2
		
		every time we do a shift operation the carry flag is set by the most significant bit 
		
		00001010 -> left shit -> 00010100 -> in this CF will be set to 0 -> which means zero (0) is overflow
		
		10000000 -> left shit -> 00000000 -> in this CF will be set to 1 -> which means one(1) is overflow
		
![[Pasted image 20210731062634.png]]
					
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
	ADD && SUB:
		-> arithmetic operations addition and subtration
		-> if the operation evaluates to a negative value, SF flag will be set, if zero ZF flag will be set
		-> ADD esp, [ebx*2] - take the value from ebx memory address muliptly with 2 and treat the result as an address take the value from it, then exp + value form the memory address and store it in esp
	cmp:
		-> internally compare just subracts both the second oporend from first and if the result is zero it sets the ZF flag
		-> cmp eax,[ebp-4] - take the value and subract it from value in eax, and if zero is the result set ZF flag
	JMP:
		-> change eip to the given address  
		-> it can be short relative (jmp 0x0e), near relative (4bytes), absolute address, caclucted address
	JNE or JNZ:
		-> jump if not equal (JNE), jump if not zep (jnz)
		-> both checks if the Zero flag is set and decide based on it
![[Pasted image 20210730143206.png]]
	
	Test:
		-> computes bit-wise logical AND of first and second oporend and sets the SF, ZF and PF status flags.
		-> TEST eax, [ebp+4]
	AND:
		-> bitwise and operation
		-> and al, bl - al = 00110011
									   bl = 01010101
								result = 00010001
	OR:
		-> bitwise or operation
		-> or al, bl - al = 00110011
									 bl = 01010101
   							  result = 01110111
	XOR:
		-> bitwise xor operation
		-> it can used to zero all bit of a register, it faster than mov operation
		-> xor al, bl - al = 00110011
									 bl  = 01010101
   							  result  = 01100110
	NOT:
		-> bitwise NOT operation
		-> NOT al - al = 00110011
   					    result = 11001100
	SHL (logical shift):
		-> first oporend is source, second oporent is the number of places to shift.
		-> it shifts the bits to left no of times given
		-> shl eax, 2 - this will shit the bits in eax twice to the left
		-> it if ofen used in muliptlicaion of numbers that are a power of two, as shitfing left multiplies the given value with 2
		-> CF flag is set with most significant bit of the result as overflow
		-> logical shift dont use the cf value to do anything
	SHR (logical shift):
		-> first oporend is source, second oporent is the number of places to shift.
		-> it shifts the bits to right no of times given
		-> shr eax, 2 - this will shit the bits in eax twice to the right
		-> it if ofen used in division if number is a power of two, as shitfing right divides the given value with 2
		-> CF flag is set with least significant bit of the result as overflow
		-> logical shift dont use the cf value to do anything
	IMUL:
		-> muliplyies the operend and stores it in both edx,eax as 32bitt * 32bit = 64bit		
		-> it can be put there ways, one oporend, then it muliplies it to the eax register 
		-> reg and value, muliptles both and put it in reg
		-> reg, value, value, it multipes given two values and puts them in the register
		-> imul with two or more oporend only takes the least significat 32 bis, thus there will no overflow
		-> imul with one oporend stores the extra bits in edx
![[Pasted image 20210731072553.png]]

	DIV:
		-> unsigned divide ax by a 8 bit value, result
		al = quotient, ah = reminder
		-> unsigned divide edx:eax by 32bit value, result
		eax = quotient, edx = reminder
		-> compiler sets edx to when the divident is 32bits
		-> if divisor is 0, a divide by zero excpetion is raised
	REP STOS:
		-> Repeat Store String, "rep" which repeat a single , instruction multiple times, so it always added as instruction prefic to some other instruction.
		->it uses ecx as counter to determine how many times it has to execute, everytime it decrements ecx.
		-> either moves one byte or dword at a time
		-> it stored the memeory location in edi
		-> it takes the value to be written in eax
		-> it increments the edi by one byte or one dword
		-> so there are 3 peices which must happen before the actual rep stos occurs. set edi to start memmory addr, ax or eax to the value to store and ecx with the number of times to store.
		
		
		


	
		










		




