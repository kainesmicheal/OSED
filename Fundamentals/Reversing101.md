##compiler

    A compiler is a program that takes a source files and generates a corresponding machine code file.  
  
	This machine code can either be a standard platform specific object code that is decoded directly by the CPU or it can be ecoded in a special plat form independent format called bytecode.  

	The biggest hurdle in deciphering compiler-generated code is the optimization applied by the most modern compilers.  

	Compilers employ a variety of techinques thta minimize code size and improve execution performance.  


	in java  

	compiler generates the bytecode and to then use a program called virtual machine to decode the byptecode and perform the operations described in it. of course, the virtual machine itself must at some point convert the byte code into standard object code that is compatible with the underlying CPU

##Operating System

    An operating system is a program that manages the computer, including the hardware and software applications
	
##Reversing Process

	System level:

		System level reversing techniques help determine the general structure of the program and sometimes even locate areas of interest within it.

	Code level:

			Code level techniques provide detailed information on a selected code chunk.  

			we observe the code from a very low level and well be seeing every little details of how the software operates. many of these details are generated automatically by the compiler and not manually by the developer, which sometimes make its difficult to understand how they relate to the program and to its functionality.
		
##disassemblers

	    Disassemblers are programs that take a program's executable binary as input and generate textual files that contain the assembly language code for the entire program or parts of it.
		
##debuggers

	    The two most basic feature in a debugger are the ability to set breakpoints and the ablity to trace through code.  
  
		When the program reaches the breakpoint, the dubugger stops and displays the current state of the program.  

		Tracing means the program executes one line of code and then freezes, allowing the user to observe the state of the program.
		
##decompilers

	    a decompiler takes an executable binary file and attempts to produce readble high level language code from it.  
  
		On the vast majority of the platforms actual recovery of the original source isn't really possible.

##High-level

	    Modules - Modules are simply binary files that contain isolated areas of a program's executable.  
  
		Two Types of Modules:  

		Static libraries:  

		→ Static libraries make up a group of source-code files that are built together and represent a certain component of a program.  
		→ They are added to a program while it is being built and becomes an integral part of the program's binary  

		Dynamic libraries (Dynamic Link Libraries(dll)):  

		→ Dynamic libraries are similar to static libraries, except that they are not embedded into the program, and they remain in a separate file, even when the program is shipped to the end user  
		→ as long as the interface it exports remains constant, a library can be replaced seamlessly without upgrading any other components in the program.  

		Procedure:  

		→ It is a peice of code, usually with a well-defined purpose, thaat can be invoked by other areas in the program.  
		→ it can optionally receive input data from the caller and return data to the called  

		Objects:  

		→ An Object is a program component that has both data and code associated with it  
		→ the code can be set of procedures that is related to the object and can manipulate its data  

		Variables:  

		→ the key to managing and storing data is usually named variables. All high level langugaes provide developers with the means to declare variables at various scopes and use them to store information.  

		Array:  

		→ the most basic and intuitive list layout, items are places sequentially in memory one after the other. Items are referenced by the code using their index number.  

		Linked lists:  

		→ each item is given its own memory space and can be replaced anywhere in memory, each item stores the memory address of the next item and somtimes also a link to the previews item.  


		Trees:  

		→ Items are hierarchically, which greatly simplifies the process of seraching for an item.

##Low level

    It is critical that you develop a sort of mental image of how high level constructs such as procedures, modules and variables are implemented behind the curtains.  
  
	One of the most important differences between high-level programming languages and any kind of low-level representation of a program is in data management.  

	The fact is that high level programming languages hide quite a few details regarding data management.  


	int Multiply(int x, int y)  
	{  
	int z;  
	z = x * y;  
	return z;  
	}



	This function as simple as it may seem, could never be directly translated into a low level representation.  

	CPU rarely have insturctions for declaring a variable or for muliplying tow variables to yield a third.  

	// might have to install this sudo apt-get install gcc-multilib  

	gcc -m32 multi.c -o multipy // to compile in 32 bits instructions  

	Register:  
	In order to avoid having to access the ram for every single instruction, microprocessors use internal memory that can be accessed with little or no performance penality.  
	Registers are small chunks of interna lmemory that reside within the processor and can be accessed very easily, typically with no performance penality whatsoever.  

	there are eight 32 bit truely geeric registers.  


	for example:  

	the most complexities revolve around data mangament. x and y can't be directly multiplied from the memory, the code must first read one of them into a register and then multiply that register by the other value that's still in the ram or copy both values into a register and then muliply them from registers  


	while reversing it is important to try and detect the nature of the values loaded into each register  


	Stack:  
	It is an area in program memory that is used for short-term storage of memory by the CPU and the program.  

	Stacks are managed as simple LIFO(last in, first out), the items are pushed and popped onto them.  

	Stack grows from higher address to lower address  

![[Pasted image 20210728151016.png]]

	Temporarily saved register values:  
	The stack is frequently used for temporarlily saving the value of a register and then restoring the saved values, the procdures might need to preserve the values of registers to ensure that it doesn't corrupt any registers used by its callers.  

	Local variables:  
	Its is a common practice to use the stack for storing local variables, local variables stored in stack are accessed using offsets.  

	Function parameters and return address:  
	The stack is used for implementing function calls. in a function call, the caller almost always passes parameters to the callee and is responsible for storing the current instruction pointer so that execution can proceed from its current position once the callee complee completes, the stack is used for storing both parameters and the instuction pointer for each procedure call.  

	HEAPS:  

	A heap is a manages memory region that allows for the dynamic allocation of variable sized blocks of memory in runtime. a program simply requests a block of certain size and receives a pointer to the newly allocated block. Heap size is always passed as a parameter to the heap allocation routine.  

	Executable data sections:  

	This area contains either global variables or pre-initialized data(hardcoded strings)  
	the compiler will emit a hard-coded address that points to the string.