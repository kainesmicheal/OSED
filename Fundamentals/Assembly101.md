##Registers

    Intel x86 has 8 General Purpose Registers  
  
	EAX -> logical or memory operations  
	EBX -> logical or memory operations  
	EDX -> logical or memory operations  
	ECX -> Counter for repetitive instructions  
	ESI -> Source pointer  
	EDI -> Destination pointer  
	EBP -> The base pointer points to the stack position right after the return address for the current function.  
	ESP -> The stack pointer stores the current position in the stack.  

	‘E’ stands for extended, as the naming convention is taken from 16bit where it was just AX, BX, DX... we can stil use those register to only use the 16 bits of a register  

	eg: MOV AX, 0x100  

	EBP and ESP is used in combination to create a stack frame  

	A stack frame can be defined as the current function's stack zone, which resided between stack pointer(ESP) and the base pointer (EBP).  

	Stack frames are used for gaining quick and conveninet access to both local variables and to the parameters passed to the current function.  

	Different portions of a register can be accessed using names  

![[Pasted image 20210728151049.png]]

##Flags

    this contains all kinds of status and system flags.  
  
	System flags are used for mangaing the various processor modes and states.  

	Status flags are used by the processor for current locgical state.  


	There are instructions that operate based on the values of the status flags, so that it becomes possible to create sequences of instructions that perform different operations based on different input values.  

	There are arithmetic instructions that test operands for certain conditions and set processor flags based on their values.  

	eg: Jcc (Conditional Jump)
	
##Instruction Format

    Instructions usually consist of an opcode and one or two operands.  

	The opecode is an instruction name such as MOV, and the operands are the “parameters” that instruction receives.  

	some instructions have no operands.  

	Register name -> The name of the general purpose register to be read from or written to. eg : EAX  

	Immediate -> A constant value embedded right in the code  

	Memory address -> the address can either be a hard coded immediate and enclosed inbrackets or evauation of some arithemtic operation or a register represends the base address of some object, and the value is take from as offset  

	MOV simply moves data from the source to the destination. the destination can either be a memory address or register  

	But only one of the operands can contain memory address and never both.  

	MOV DestinationOperand, SourceOperand  

	eg: MOV EAX, [0xdeafbeef]  
  
  
![[Pasted image 20210728151116.png]]
  
  
	CMP simply subracts Operand2 from Operand1 and if the result of the subration is zero, the Zero Flag is zero, which indicated that the two operands are equal.  

	CMP Operand1, Operand2  

	Jcc TargetCodeAddress  

	if the specifies condition statisfied, Jcc will just update the instuction pointer to point to TargetCodeAddress without saving the current value.  
	if the conditoin is not satisfied, jcc will simply do nothing and execution will proceed at the following instruction.  

	The CALL instuction calls a function and the RET instruction returns to the caller.  

	The CALL instruction pushes the current instruction pointer onto the stack(so that it is later possible to return to the caller) and jumps to the specified address.  

	CALL Function address  

	The RET instruction pops the instruction poiner pushed to the stack by CALL and resumes the execution form that address.  

	Additionally RET can be instucted to increment ESP by the specified number of bytes after popping the instructin pointer, This is neede for restoring ESP back to its original position.
	
##Compiler Architecture

    Developing an understanding of the process undertaken by compilers and the way they “perceive" the code will help in eventually desiphering their ouput.  
  
  
	During the translation process, compilers usually go through numerous improvements or optimization steps that take advantage of the compiler's understanding of the program and employ various algorithms to improve the code's efficiency.  

	The average compiler consists of three basic components. the front end is reponsible for deciphering the original program text and for ensuring that its syntax is correct and in accordance with the language's specifications. the optimizer imporves the program in one way or another, while preserving the original meaning. finally the back end is responsible for generating the platform specific binary from the optimized code emitted by optimizer.  

	Front-end:  
	It starts with a process called lexical analysis or scanning, in which the compiler goes over the scource file and scans the test for individual tokens within it, to match the language rules, if it valid, it converts it to the compiler's intermediate representaions. this step doesnt change or improve anything so this doent concern reversers.  

	Intermediate Representations:  
	Properly choosing the intermediate representation of code in a compiler is one of the compiler designer's important design decisions.  
	The layour heavily depends on what kind of source the compiler takes as input and what kind of object code the compiler spews out.  
	Its is not uncommon for compilers to have two or more intermediate representations, one for each stage in the compilation process.  

	Optimizer:  
	The two primary goals for optimizers are usually either generating the most high-performance code possible or generation the smallest possible program binaries.  
	Optimizations that take palce in the optimizer are not processor-specific and generic improvements made to the original program's code without any relation to the specific platform to which the program is targeted.  

	Code Structure:  
	Loops can often be partially or fully unrolled.  
	Unrolling a loop means that instead of repeating the same chunk of code using a jump instruction, the code is simply duplicated so that processor executes it more than once. this makes the resulting binary larger, but has the advantage of completely avoiding having to manage a counter and invoke conditional branches. It is also possible to partially unroll a loop so that the number of iterations is reduced by performing more than one iteration in each cycle of the loop.  
	when going over switch blocks, compilers can determine what would be the most efficient approch for searching for the correct case in runtime (different searching methods)  

	Redundany Elimination:  
	Optimizers have algorithms that serach for such redendancies and eliminate them.  

	Back-end:  
	The intermediate representation is converted into platform specfic binary code.  
	It is responsible for the actual selection of specific assembly language instructions.  
	this component has enough information to apply any significant platform-specific optimizations.  

	Instruction Selection:  
	This is where the code from the intermediate represenataion is translated into platform specific instructions.  

	Register allocation:  
	The fact that the target processor has a limited number of registers comes into play during code generation, when the compiler must decide which variable gets placed in which register and which variable must be placed on the stack.  

	Instruction Scheduling:  
	It employs platform specific instuction scheduling algorithms that reorder instructions to try to achieve the highest possible level of parallelism.  
	the end result is interleaved code, where two instruction sequences dealing with two separate things are interleaved to create one sequence of instructions.  

	Listing Files:  

	A listing file is a compiler generated text file that contains the assembly language code produced by the compiler  
	A listing file conveniently shows how each assembly language line maps to the origin source code.  
	this can be used to study the behavoir of a specific compiler by feeding it difference code and observing the output through listing file.
	
##Execution Environment

    Execution environments are especially important to reversers because the architectures often affect how the program is generated and compiled, which directly affects the readability of the code and hence the reversing process.  
  
	Bytecodes:  

	The interesting thing about virtual machines is that they almost always have their own bytecode format. this is essentially a low-level language that is just like a hardware processor's assembly language.  

	Interpreters:  
	The original approach for implementing virtual machines has been to use interpretes. interpreters are programs that read a program' s bytecode executable and decipher each instruction and execute it in a virtual environment.  

	Just-in-Time compilers:  
	Modern implementations avoid using interpreters because of the performance issues described above, instead they employ justintime compilers or JITs,  
	The idea is to take snippets of program bytecode at runtime and ocmpile them into the native processors' machine language before running them  
	The chunks of bytecode are compiled on demand
	
##micro-ops

    x86 processors use microcode for implementing each instruction supported by the processor.  

	Microcode is essentially another layer of programming that lies within the processor. this means that the processor itself contains a much more primitive core, only capable of performing fairly simple operations.  

	The process of constanly fetching instruction microcode from ROM can create significant performance bottlenecks, so it employs an exection trace cache that is responsible for caching the microcodes of frequently executed instrutions.
	
##pipelines

    Basically, a CPU pipeline is like a factory assembly line for decoding and executing program instructions.  
  
	Front end:  
	Responsible for decoding each instruction and producing sequences of micro-ops that represent each instruction, these micro ops are then fed into the out of order core.  

	Out of Order Core:  
	This component receives sequences of microops from the front end and reorders them based on the availability of the various resources of the processor. the idea is to use the available resources as aggressively as possible to achive parallesim. the ability to do this depends heavily on the original code fed to the frontend. given the right conditions the core will actually emit multiple microops per clock cycle.  

	Retirement Section:  
	the retiremenrt section is primarily responsible for ensuring that the original order of insturctions in the program is preserved when applying the results of the out-of-order execution.  

	In terms of actual execution of operations, the architecture provides four execution ports(each with its own pipeline) that are responsible for the actual execution of instructions.  

![[Pasted image 20210728151146.png]]

	Notice how port 0 and port1 both have double-speed ALUs this is significant aspect of x86 because it means that each ALU can actually perform two operations in a single clock cycle. for example it is possible to perform up to four additions or subtrations during a single clock cycle(two in each double speed ALU), on other hand a floating point operations are pretty much guaranteed to take at least one cycle because there is only one unit that actually performs floating-point operations.  

	Branch prediction:  
	Normally, the processor simply fetched the next instructino from memory whenever there is room for it, but what happens when there is a conditional branch in the code?  
	Conditional branches are a problem because often their outcome is not known at the time the next instruction must be fetched.  

	The solution to these problem is to tyr and predict the result of each conditional branch. based on this prediction the processor fills the pipeline with instructions that are located either ight after the branch insturction or form the branch's target address. A missed prediction is usually expensive and requires the entire pipline be emptied.  

	in order to improve the processor's predictino abilities processors employ a branch trace buffer(BTB) which records the results of the most recent branch instructions processed. This way when a branch is encountered, it is searched in the BTB. if an entry is found, the processor uses that information for predicting the branch.