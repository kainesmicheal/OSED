##Virtual memory and pagging

    The idea is that instead of letting software directly access physical memory, the processor, in combination with the operating system, creates an invisible layer between the software and the physical memory,  
  
	for every memory access, the processor consults a special table called the page table that tells the process which physical memory address to actually use.  

	Beyon address spaces, the existence of a page table also means that it is very easy to instruct the processor to enforce certains rules on how memory is accessed.  

	for example:  

	page-table enttires often have a set of flags that determine certain properties regarding the specific entry such whether it is accessible from nonprivelged mod. this means that the operating system code can actually reside inside the process's address and simply set a flag in the page-table entries that restricts the application from ever accessing the operating system's sensitive data.  


	Paging is process whereby memory regions are temprrily flushed to harddisk when they are not in use.  

	Page faults:  
	when the page's page table entry is invalid, the processor generates a page fualt, which the operation sytem resolves by simply loading the page's content from the paging file and resuming the program that originally triggered the fault.  

	Working sets:  

	a working set si a per process data structure that lists the current physical pages that are in use in the process's address space.  
	The system uses working sets to determine each process''s active use of physical memory and which memory pages have not been accessed in a while. such pages can then be paged out to disk and removed from the process' s working set.
	
##Kernel mode

	It is basically the windows term for privileged processor mode and is frequently used for describing code that runs in privileges mode or memory that is only accessible while the processor is in privileged mode  

	windows uses a 32 bit 4gp memory address that is typically divided into two 2GP portions  

	2GP application memory portion  
	2GP shared kernel memory portion  

	the general ideas is the upper 2gp contain all kernal-related memory in the system and are share among all address spaces.  

	One side effect of this design is that applications only have a 31 bit address space, the most significant bit is always clear in every address. this proviedes a tiny reversing hint:  

	A 32bit number whose first hexadecimal digit is 8 or above is not a valid user-mode pointer  

	what goes on inside those2gp reserved for the kernel,  

	the kernel space contains all of the system's kernel code, including kernel itself and many other kernel components in the system.  

![[Pasted image 20210728153515.png]]

	Paged and Nonpaged pools:  
	The paged pool and nonpaged pool are essentially kenrnel mode heaps that are used by all the kernel components. because they re stored in kernel memory the pools are inehrenly available for all address spaces, but are only accessible from kenrel mode code.  
	the paged pool is a heap the is made up of conventional paged memory.  
	the non paged pool is a heap that is made up of non pageble memory, as it could never be flushed to the hard drive and allways kept in physical memory. this is beneficial because siginificant areas of system are not allowed to use pagable memory.  

	System cache:  
	the system cache space is where the windows cache manager maps all currently cache files. caching is implemented in windows by mapping files into memory and allowing the memory manager to manage the amout of physical memory allocated to each mappedfile  
	when a program opens a file, a section object is creater for it and mapped into the system cache area. when the program later accesses the file using readfile or writefiel API, the file ystem internally access the mapped copy of the file using manager APIs such as cccopyread and cccopywrite  

	Terminal services session space:  
	This memory area is used by the kernel mode component of the win32 subsystem: win32k.sys  
	it is a component of windows service that allows for multiple, remote GUI sessions on a single windows system.  
	thus win32 memory space “session private” can essentially load multiple instances of the win32 subsytem  
	in the kernal each instance is loaded into the same virtual address but in a differen session space.  

	Page Tables and Hyper Space:  
	these regions contain process-specfic data that defines the current process's address space. the page table area is simply a virtual memory mapping of the currently active pages in the page tables.  
	hyper spaces is used for serveral things, but primarily for mapping the current process's working set.  

	System working set:  
	it is the way system keeps track of the pages that are currently in use  
	The two largest memory regions that are managed by this data structure are the paged pool and the system cache  

	System page table entries:  
	it is just a virtual memory space that can be used by kernel and by drivers whenever they need a large chunk of virtual memory.
	
##section objects

	section object is a special chunk of memory that is manged by the operating system.  

	Before the contents of the section object can be accessed the object must be mapped.  
	mapping a section object means that a virtual address range is allocated for tthe object and that it then become accessible throught htat address range.  

	one of the key properties of section oject is that they can be mapped to more than one place.  
	this makes section objects a convenient tool for applications to share memory between them.  
	the system also uses section objects to share memory between the kernel and user-mode processes.  

	in windows section object are also called as memory mapped files  

	two types of section objects:  
	pagefile-backed:  
	-> it can be used for temporary storage of information, and is usually created for the purpose of sharing data between two processes or between applications and kernel  
	-> the section is created empty and can be mapped to any address space  
	-> it can be paged out ot a pagefile if required  

	File-backed:  
	-> it is attached to a physical file in drive, it contains the contents of the file to which it is attached. if writable any changes made to the data while the object is mapped into memory will be written back into the file.  
	-> this provides a way to directly access the data in memory using pointer, instead of using API like readfile and writefile
	
##Virtual Address Descriptor

	→ it is the data structure used by windows for managing each individual process's address allocation.  
	→ it is a binary tree that describes every address range that is currently in use.  
	→ each process has its own individual tree, and within those trees each entry describes the memory allocation in question.  

	Mapped allocations:  
	they are memory mapped files that are mapped into the address space.  
	this includes all executables loaded into the process address space and every memory mapped file mapped into the address space.  

	Private allocations:  
	they are allocations that are process private and were allocated locally  
	it used for heaps and stacks (there can be multiple stacks in single process one foreach thread)
	
##User mode

    when the system is in user mode, it can only run user-mode code and only access usermode memory  
  
	we can't be as specific as we were in our earlier discussion of the kernel address space, every application is different.  

	Private Allocations:  
	these are the most basic types of memory allocations in a process. this is the simple case where an application requests a memory block using the virtualAlloc win32 api, this is most primitive type of allocation, because it can only allocate whole pages and nothing smaller than that.  

	eg: stack and heaps  

	Heaps:  
	Heap is a data sturcture that enables that creation of multiple variablesized blocks of memory wisely so that applications can conviently allocate and free variable-sized blocks as required  
	most windows applications dont directly call virtualAlloc instead they allocate a heap block by calling a runtime library function such as malloc or by calling a system heap API such as heapAlloc.  

	Stacks:  
	system allocates a stack automatically for every thread while it is being created.  

	Executable:  
	the system runs application code by loadin it into memory as a memory mapped file  

	Mapped views(sections)  
	applications can create memeory mapped files and map them into their address space. it is convenient for sharing memory between two or more programs
	
##Memory management api

    The windows virtual memory manager is accessible to application programs using a set of win32 APIs that acan directly allocate and free memory blocks in user-mode address spaces.  
  
	virtualAlloc:  
	this function allocates a private memory block within a user-mode address space.  
	this is a low-level memory block whose size must be page-aligned  
	this is not a variable-sizd heap bloack as allocated by malloc.  
	it can either be reserver or actually committed  
	reserving a block means that we simply reserve the address space but dont actually use up any memory. committing a block means that we actually allocate space for it in system page file. no hysical memory will be used untill the memory is actually accessed.  

	virtualProtect:  
	this function sets a memory region's protection settings, such as whether the block is readable, writable, or executable  
	i can be used to change whether the block is cached by the hardware or not  

	virtualQuery:  
	this function queries the current memory block (essentially retrieving information for the block's VAD node)  
	information like what type of block it is(private, section, image) and whether its reserved, commited, or unused.  

	virtualFree:  
	this function frees a private allocation block.  

	all of these APIs deal with the currently active address space, but windows supports virtual-memory operations on other processes, if the process is privileged enough to do that.  

	all the api listed here have a Ex version(VirtualAllocEx, VirtualQueryEx) that receive a handle to a process object and can operate on the address spaces of processes other than the one curretnly running.  

	windows all offers two apis that actually access another process's address space and can read or write to it. these api are readprocessmemory and writeprocessmemory.  

	section object or memory mapped file can be created using createfilemapping api  
	the section object can be mapped into the user-mode address space using the mapviewoffileEx api and can be unmapped using unmapviewoffile api.
	
##Object and Handles

    The window kernel manages objects using a centralized object manager component.  
  
	object manager is reponsible for all kernel objects such as sections, file and device objects, synchronization objects, processes, and threads.  

	it is important to understand that this component only manages kernel-related objects.  

	gui related objects such as windows, menu and deivce contexts are manged by seperate object managers that are implemented inside win32k.sys  


	all of these objects are merely data structures, they are typically stored in non paged pool kernel memory.  

	all objects use a standard object header that describes properties such as its type, reference count, name and so on.  

	the object manager is not aware of any object specific data-structures, only of the generic header.  


	Kernal code typically accesses objects using direct pointers to the object data structures, but application programs obviously can't do that, instead, applicatins use handles for accessing individual objects.  

	Handles:  

	A handle is a process specific numeric identifier which is essentially an index into the process's private handle table.  
	Each entry in the handle tables contians a pointer to the underlying object, which is how the system associates handles with objects.  
	along with the object pointer, each handle entry also contains an access mask that determines which types of operations that can be performed on object using specific handle.  

	the object's access mask is a 32-bit integer that is divided into two 16bit access flag words.  

	the upper words contains generic access flags such as GENERIC_READ and GENERIC_WRITE  
	the lower words contains object specific flags such as PROCESS_TERMINATE, which allows you to terminate a process using its handle, KEY_ENUMURATE_SUB_KEYS, which allows you to enumurate the subkeys of an open register key.  

![[Pasted image 20210728153813.png]]


	For every object, the kernel maintains two reference counts: a kernel reference count and a handle count.  

	Objects are only deleted once they have zero kernel references and zero handles.
	
##names objects

    Some kernal objects can be named, which provides a way to uniquely identify them throughout the system.  
  
	suppose, for example, that two processes are interested in synchronizing a certain operation between them.  

	a typical approach is to use a mutex object, but how can they both know that they are dealing with same mutex?  

	the kernel supports object names as a means of identification for individuals objects. in our example both processes could try to create a mutex names testMutex.  
	whoever does that first will actually create the testMutext object and the second program will just open a new handle to the object.  

	when a object creation api such as CreateMutex is called for an object that already exsists, the kernel automatically locates that object in the global table an returns a handle to it.  

	Names objects are arranged in hierarchical directories, but the win32 api restricts user-mode applications' access to these directories.  

	BaseNamedObjects:  

	This directory is where all conventional win32 named objects, such as mutexes, are stored. all named-object win32 apis automaticallu use this directory. applications programs have no control over this.  

	Devices:  

	This directory contains the device objects for all currently active system devices.  
	generally speaking each device driver had at least one entry in this directory.  
	logical devices such as TCP, physical devices such as harddisk  

	win32 api can never directly access object in this directory, they must use symbolic links  

	Global??:  
	it is the symbolic link directory. (also named ?? in older versions of windows)  
	Symbolic links are old-style names for kernel objects.  

	think about assiging each dirve a letter, such as C:  
	and about accessing physical devices using an 8 letter name that ends with colon, such as COM1:  
	in modern versions of windows they are linked to real devices in the devices directory using symbolic links.  
	win32 applications can only access devices using their symbolic link names  

	Some kernel object are unnamed and are only identified by their handles or kernel object pointers.  

	a good example of such object is a thread object, which is created without a name and is only represented by handles(form user mode) and by direct pointer into the object( form kernel mode).
	
##Processes and Threads

    Processes:  
		A process is a fundamental building block in windows  
		A process is many things, but it is predominantly an isolated memory address space.  
		This address space can be used for running a program  
		address spaces are created for every program in order to make sure that each program runs in its own address space.  
		inside a process's address space the system can load code modules, but in order to actually run a program, a process must have at least on thread running.  

	Threads:  
		a thread is a primitive code execution unit.  

		At any given moment, each processor in the system is running one thread, which is effectively means that its just running a peice of code. this can be either program or operating system code, it doesn't matter.  
		the idea with threads is that instead of continuning to run a single peice of code until it is completed, windows can decide to interrup a running thread at a given moment and switch to another thread  

	this process is at the very heart of windows' ability to achieve concurrency.  

	Internally, a thread is nothing but a data structure that has a CONTEXT data structure telling the system the state of the processor when the thread last ran, combined with one or two memory blocks that are used for stack space.  

	struct thread {  
	CONTEXT current_state;  
	STACK user;  
	STACK kernel;  
	}; // this is just to imagine not the actuall representaiton  

	when you think about it, a thread is like a little virtual processor that has its own context and its own stack.  

	the real physical processor switches between mutiple virtual processors and always starts execution from the thread's current context information and using the thread's stack.  

	the reason a thread can have two stacks is that in windows threads alternte between running user-mode code and kernel-mode code.  

	for instance a typical application threads runs in user-mode, but it can call system apis that are implemented in kernel mode.  

	in such case the system api code run in kernal mode withing the calling thread, beacuse the thread can run in both user and kernel mode, it must have two stacks.  

	seperating the stack is a basic secuirty requirement.  

	the components that manage threads in windows are the scheduler and the dispatcher, which are together responsible for deciding which thread gets to run for how long and for performing the actual context switch when its time to change the currently running thread.  


	windows arch kernel is preemptive and interruptible, meaning that a thread can usually be interrupted while running in kernel mode just as it can be interrupted while running in usermode  

	some internal kernal components cant be interruppted(like the sheduler itself)
	
##Context Switching

    the first step is for the kernel to let a thread run.  
  
	all this means in reality is to load its context (this means entering the corrent memory address space and intializing the values of all CPU registers) and let it start runnig.  

	the thread then runs normally on the processor until the time comes to switch to a new thread.  

	the truth is that threds frequently just give up the CPU on their own volition, and the kernel doesn't even have to actully interrupt them.  
	this happens when a program is waiting for somthing.  

	in windows one of the most common example is when a program calls the GetMessage win32 API. GetMessage is called all the time, it is how applications ask the system if the user has generator any new input events(such as pressing a key or somehting)  

	in most cases, GetMessage accesses a message queue and just extracts the next event, but in some cases there just aren't any messages in the queue. so it will enter to waiting mode  
	like telling the kernel, “im all done for now, wake me up when a new input event comes in.”  

	at this point the kernel saves the entire processor state and switched to run another thread. as one wouldnt want the processor to just stall because a single program is idling for the moment.  

	what happens when a thread doesn't just give up the processor.  

	this could easily happen if it just has a lot of work to fo.  

	think of a thread performing some kind of complex algorithm, which would take hours to complete  

	to avoid this we use what called preemptive sheduling, which means that threads are given a limited amount of time to run before they are interrupted.  

	Every thread is assigned a quantum, which is the maximum amount of time the thread is allowed to run continously, while a thread is runnig, the os uses a low-level harware timer interrupt to monitor how long its been running  
	once the thread's quantum is up, its is temporarily interrupted and the system allows other threads to run, the kernal stores the state of all CPU registers before suspending the thread and restores that state when the thread is resumed. this way the thread has no idea that it was ever interrupted.
	
##Synchronization Objects

    the existence of thread is a mixed blessing. on one hand threads offer remarkable flexibility when developing a program, on the other hand, synchronizing mutiple threads within the same programs is not easy, especially ebacuse they almost always share data structures between them.  
  
	probably one of the most important aspects of desigining mulitthreaded software is how to properly design data structures and locking mechanisms that will ensure data validity at all times.  

	The basic design of all synchronization objects is that htey allow tow or more threads to competed for a sinlge resource and they help ensure that onlly a controlled number of threads actually access the resource at any given moment.  

	threads thatt are blocked are put in a special wait state by the kernel and are not dispached untill wait state is satisfied.  

	this is the reason hwy synchronization objects are implemented by the operation system. the scheduler must be aware of their existence in order to know when a wait state has been satisfied and a specific thread can continue execution.  

	windows supports serveral builtin synchronization objects, each suited to specific types of data-structure that need to be protected.  

	Events:  
	an event is simple boolean sync object that can be either set true or false. An event is waited on by one of the standard win32 wait api suchas waitforsingleobject or waitformultipleobjects  

	Mutexex:  
	a mutex is an object that can only be acquired by one thread at any given moment. any threads that attempt to acquire a mutex wilie it is already owned by another thread will enter a wait state untill the original thread releses the mutex or untill it terminated. if more than one hread is waiting. they will each receive ownership of the mutex in the original order in which they requested it.  

	Semaphores:  
	a semaphore is like a mutex with a user-defined counter that defines how many simultaneous owners are allowed on it. onve that maximum number is exceeded, a thread that requests owenership of the semaphore will enter a wait state untill one of the threads release the semaphore  

	Critical Sections:  
	a critical section is essentially an optimized implementaion of a mutex.  
	it is logically indetical to a mutex, but with the difference that it is process private and that most of it is implemented in usermode.  
	all the sync objects described above are managed by the kernel object manager and implemented in kernel mode, which means that the system must switch into the kernel for any operation that needs to tbe preformed on them.  
	a crititcal section is implemented in user mode and the system only switches to kernel mode if an actual wait is neccessary.
	
##Process initialization Sequence

    these are the following steps taken by the system in an average process creation sequence.  
  
	→ when a process calls the win32api CreateProcess, the api creates a process object and allocates a new memory address space for the process  
	→ createprocess maps ntdll.dll and the program executalble (the .exe file) into the newly created address space.  
	→ create process creates the process's first thread and allocates stack space for it.  
	→ the process's first thread is resumed and starts running in the LdrpInitialize function inside ntdll.dll  
	→ Ldrpinitialize recursively traverses the primary executable's import tables and maps into memory every executable that is required for running the primary executable.  
	→ at this point control is passed into LdrpRunInitializeRoutines which is an internal ntdll.dll routine responsible for intializing all statically linked dlls currently loaded into the address space.  
	→ the initialization process consists of calling each dll's entry point with the DLL_PROCESS_ATTAACH constant.  
	→ Once all the dlls are initalized ldrpinitialize calls the thread's read initialization routine, which is the baseprocessstart function from kernel32.dll. this function in turn calls the executable's winmain entry point at which point the process has completed its initialization sequence.

##Win32 API

    win32 is a very large set of functions that make up the official low-level programming interface for windows applications.  
  
	microsoft introducded simpler, higher level interfaces that exposed most of the features offered by the win32 api.  

	MFC (microsoft foundation classes), which is a hierarchy of c++ objects that can be used for interacting with windows  

	.NET framwork uses the system class for accessing os system services.  

	The code win32 api constains roughly 2000 apis (it depends on the specific windows version)  

	they are divided into three categories: kernel, USER and GDI  

![[Pasted image 20210728154146.png]]

	Kernal API:  
	→ it is also called as BASE api  
	→ it is implemented in the kernel32.dll module and include all non-gui related services, such as file i/o, memory mangement, and so on.  
	→ kernel32.dll typically calls low-level native api form ntdll.dll to implement the various services.  
	→ kernel apis are used for creating and working with kernel-level objects such as files, synchronization objects and so on.  

	GDI api:  
	→ it is implemented in the GDI32.dll and include low-level graphics services such as those for drawing a line, displaying a bitmap, and so on.  
	→ GDI apis are primarily implemented in the kernel, inside the win32k.sys module.  
	→ GDI apis make system calls into win32k.sys to implement most apis.  

	USER api:  
	→ it is implemented in the user32.dll module and include all higher-level GUI related services such as window-management, menus, dialog boxes so on.  
	→ all gui objects are drawn by user using GDI calls to perform the actuall drawing. user heavily relies on GDI to do its buisness.  

	native api:  
	→ the native api is the actual interface to the windows NT system.  
	→ the native api is the most direct inter face into the windows kernel, providing interfaces for direct inferfacing with memory manager, i/o system, object manager, processes and threads so on.  
	→ Technically the native api is a set of functions exported from both ntdll.dll (for user-mode callers) and from ntoskrnl.exe (fo kernel-mode callers).  
	→ APIs in the native api always start with one of two prefixes either Nt or Zw  
	→ functions have name like NtCreateFile or ZwCreateFile  
	→ in user-mode implementation in ntdll.dll, the two groups of api are identical and actually point to the same code.  
	→ in kernel-mode the Nt versions are the actual implementation of the apis while the Zw versions are stubs that go through the system-call mechanism.  
	→ the reason you would want to go through the system-call mechanism when calling an api from kernel mode is to prove to the api being called that youre actually calling it from kernel mode  
	→ calling Zw api is a way to simplify the process of calling functions because you can pass regular kernel mode pointers.
	
##System calling mechanism

    A system call takes place when user-mode code needs to call an operating system API.  
  
	the user-mode side of the api usually performs basic paramter validation checks and calls down into the kernel to actually perform the requested operation,  

	it is not possible to directly call a kernel function from user mode, that would create a serious vulnerability because applications could call into invalid address within kernel and crash the system or even call into an address that would them to take control of the system.  

	this is why operating systems use a special mechanism for switching from user mode to kernel mode.  
	the general idea is that the user-mode code invokes a special CPU instruction that tells the processor to switch to its privileged mode (the CPU terminology for kernel mode execution) and call a special dispatch routine.  
	this dispatch routine then calls the specific system function requested from user mode.  

	in windows 2000 and earlier, the system would invoke interrupt 2E in order to call into the kernel.  


	ZwReadFile:  

	mov eax, 0xa1  
	lea edx, [esp+0x4]  
	int 2e  
	ret 0x24



	eax register is loaded with the service number  
	edx points to the first parameter that the kernel mode function receives.  
	when the int 2e instruction is invoked, the processor uses the interrup descriptor table(IDT) in order to determine whihc interrupt handler to call.  
	IDT is a processor owned table that tells the processor which orutine to invoke wherever an interrupt or an exception takes place.  
	the IDT entry for iterrupt 2E points to internal NTOSKRNL function called kisystemservice, whihc is the kernel service dispatcher. kisystemservice verifies that the serivce number and stack poiniter are valid and calls into the specific kernal function requeuested.  


	Most recent versions of the operating systems use the optimized version of the same mechanism  

	instead of invokeing an interrupt in order to perform the switch to kernel mode, the system nowuses the special SYSENTER instruction in order to perform the switch.  

	SYSENTER is essentially a high-performance kernel-mode switch instruction that calls into a predetermined function whole address is stored at a special mode specific register(MSR) called SYSENTER_EIP_MSR  


	ZwReadFile:  

	mov eax, 0xbf  
	mov edx, 0x7ffe0300  
	call edx  
	ret 0x24  


	SystemCallStub: // location 7ffe0300  

	mov edx, esp  
	sysenter  
	ret




	If youre wondering why this extra call is required (instead of just invoking SYSENTER from within the system api)  

	it is because sysenter records no state information, in previous implementaion the invocation of int 2e would store the current value of the EIP and registers  

	so by calling into the systemcallstub the os is recording the address of the current usermode stub so that it know where to return later.
	
##Executable Formats

    The basic structure of window's executable file format: the Portable Executable (PE).  
  
	they're relocatable, this simply means that they could be loaded at different virutal address each time they are loaded. (but they can never be relocated after they have been loaded.)  

	executables contains many cross-references, where one position in the code is pointing at another position in th code.  

	to tackle this  

	each module is assigned a base address while it is being created. the linker then assumes that the executable is going to be loaded at the base address, if it does, no relocation will take place. if the module's base address is already taken, the module is relocated.  

	whenever you have a pointer inside the executable header, itll always be in the form of a relative virtual address(RVA), an RVA is just an offset into the file.  

	when the files is loaded and is assigned a virtual address, the loader calculates real virtual addresses out of RVAs by adding the module's base address to a RVA.  

	Image sections:  

	An executable image is divided into individual sections in which the file's contents are stored  
	sections are needed because different areas in the file are treated differently by the memory manager when a module is loade.  

	a common division is to have a code section also called as a text section containing the executable's code  
	data section containing the executable's data.  
	in load time, the memory manager sets the accees rights on memory pages in the different sections based on their settings in the section header.  
	this determines whether a given section is readble, writable, or executable.  

	the code section contains the executable's code, and the data sections contain the executable's initialized data, which means they contain the contents of any initialized variable defined anywhere in the program.  

	char szMessage[] = “Welcome to my program!”;  

	regardless of where such a line is places within a c/c++ program, the compiler will need to store the string somewhere in the executable. this is considered initialized data. the string and the variable that point to it will both be stored in a intialized data section.  

	Section Alignment:  
	Because individual sections often have different access settings defined in the executable header, and because the memory manger must appy these access settings when an executable image is loaded into memory.  
	on the other hand, it would be wasteful to actually align executables to a page boundary on disk that would make them significantly bigger than they need to be.  

	because of this, the PE header has two different kinds of alignments fields:  

	Section alignment  
	File alignment  

	Section alignment is how sections are aligned when the executable is loaded in memory and file alignment is how sections are aligned inside the file, on disk.  

	alignment is important, as TVA is to relative to the begining of the image(base address)  

	this means that if you just open an executable as regular file and access it, RVA's wont point to the right place, as RVA are computed using the file's section alignment and not using file alignment.  


	Dynamic linked libraries:  
	dynamic linked libraries(DLLs) are a key feature in a windos. the ideas is that a program can be broken into more than one executable file, where each executable is responsible for one feature or area of program functionality.  
	the benfit is that overall program memory consumption is reduced.  
	the system can detecht that a certain executable has been loaded inot more than one address space and just map it into each address space instead of reloading it into a new memeory location.  

	compile time static linked libraries:  
	the code in the .lib file is statically linked right into the exe while it is built, just as if the code in the .lib file was part of the original program source code. when the executable is loaded the os has no way of knowing that parts of it came from a library.  
	if another exe gets loaded that is also statically linked to the same library, the library code will essentially be loaded into memory twice, because the os will have no ideas that two exes contain parts that are identical  

	windows programs have two different methods of loading and attaching to dlls in runtime  

	Static linking  
	Runtime linking  

	Static linking:  
	this is not to be consfuced with compile time static linking  
	it refres to a process where an exe contains reference to another exe within its import table.  
	Static linking is implemented by having each module list the module it uses and the function it calls within each module(this is called the import table)  
	when the loader loads such an executable, it also loads all the modules that are used by the current module and resolves all external references os that exe holds valid pointers to all exeternal functions it plans on calling.  

	Runtime linking:  
	Runtime linking refers to a different process whereby an exe can decide to load another exe in runtime and call a function from that exe.  


	the princplie difference between these two methods is that with dynamic linking the program must manually load the right module in runtime and find the right function to callby searching through the exe's headers. runtime linking is more flexible  

	Imports and exports:  

	imports and exports are the mechanisms that enable the dynamic linking process of executables described earlier.  

	consider an executable that references functions in other executables while it is being compiled and linked, the compiler and linked have no idea of the actual addresses of the imported functions.  
	it is only in the runtime that these addresses will be known. to solve this problem, the linker creates a special import table that lists all the functions imported by the current module by their names.  
	the import table contains a list of modules that the module uses and the list of functions called within each of the modules  

	when the module is loaded, the loader loads every module listed in the import table and goes to find the address of each of the functions listed in each module.  

	the addresses are found by going over the exporting module's export table, which contains the names and RVAs of every exported function.  


	when importing module needs to call into a imported function, the calling code typically looks like this  

	call [some address]  

	where some address is a pointer into the executable import address table(IAT) when the module is linked the IAT is nothing but an list of empty values, but when the modlue isloaded, the linked resolves each entry in the IAT to point to the actuall functions in the exporting module.  

![[Pasted image 20210728154327.png]]

	Directories:  
	PE executables contain a list of special directories, which are essential additional data structures that executables may contain.  

	most of the directories have a special data structure that describes their contents, and none of them is required for an executable to function properly  

	export table -> image_export_dirctory -> lists the names and RVAs of all exported functions in the current module.  

	import table -> image_import_descriptor -> lists the names of module and functions that are imported from the current module.  

![[Pasted image 20210728154342.png]]
![[Pasted image 20210728154356.png]]

##Input && Ouput

    I/O system is a combination of kernel components that manage the device drivers running in the system and the communication between applications and deivce drivers.  

	device drivers register with the i/o system, which enables applications to communicate with them and make genric or device specific requests from the device.  

	generic requests include basic tasks such as having a file system read or writing to a file.  

	the i/o system is responsible for relaying such request from the applications to device driver responsible for performing the operation.  

	the i/o system is layered, which means that for each deivce there can be multiple device drivers that are stacked on top of each other. this enables the creation of a generic file system driver that dosen't care about the specific storage device that is used.  

	in the same way it is possible to create generic storage drivers that don't care about the specific file system driver that will be used to mange the data on the device.  

	I/O will take care of connecting the two components togethter and because they use well-defined i/o system interfaces, they will be able to coexist without special modifications  

	this layered architecture also makes it relatively easy to add filter drivers, which are additional layers that monitor or modify the communications between drivers and the applications or between two drivers. thus it is possible to create generic data processing drivers tha perform some kind of pocessing on every file before it is sent to the file system. (like a transparent file-encryption driver)  

	the I/O system is interesting to us as reversers because we often monitor it to extract information regarding our target program.  

	this is usally done by tools that insert special filtering code into the device heirarchy and start monitoring the flow of data.
	
##win32 sub system

    the win32 subsystem is the compoenent responsible for every aspect of the windows user interface.  
  
	this starts with the low-level graphics engine, the graphics device interface (GDI) and ends with the USER component, whihc is reponsible for higher-level GUI constructs such as windows and menus and for processing user input.  

	win32 subsystem is implemented inside the win32k.sys kernal component and is conrolled by user32.dll and gdi32.dll user components  

	object management:  

	both USER and GDI maintain object tables that are quite similar in layout. handles to win32 objects such as winows and deivce contexts are essentially indexes into these object tables.  

	the tables are stored and managed in kernel memeory, but also mapped into each process's address space for readone access from user mode.  

	unlike kernel object handles, both user and gdi handles are global, if more than one process needs to access the same object, they all sahre the same handles, in reality, the win32 subsystem deosent always allow more than one process to access the smae objects;
	
##Structured Exception Handling

    Exception is a special condition in a program that makes it immediately jump to a special function called an exception handler.  
  
	the exception handler then decides how to deal with the exception and can either correct the problem and make the program continue from the same code position or resume execution from another position.  

	an exception handler can also decide to terminate the program if the exeception cannot be resolved.  

	there are two basic types of exceptions:  

	hardware exceptions and software exceptions  

	hardware exceptions generated by the processor, for example when a program accesses an invalid memory page or when a division by zero occurs. a software exception is generated when a program excpicitly generates an exception in order to report an error.  
	in c++ for example an exception can be raised using the throw keyword, which is a commoly used technique for propagating error conditions  

	in windows, the throw keyword is implemented using the raiseException win32 api which goes down into the kernel and follow a similar code path as a hardware exception. eventually returning to user mode to notify the program of the exception.  

	Structured exception handling means that the operating system provides mechanisms for distributing execeptions to applications in an organized manner. each thread is assigned an exception handler list  

	when a expetion accours the os calles each of the registered handlers and the handlers can decide whether they would like ot handle the exception  

	the exeception handler list is stored in the thread information block (TIB) data structure which is available from user mode and contins following feilds  
  
![[Pasted image 20210728154536.png]]
  
	the TIB is stored in a regular private allocation usermode memory. we already know that a single process can have multiple threads, but all threads have own TIB data structure,  

	windows uses FS segment register to as a pointer to the currently active thread specific data structures  

	the current threads TIB is always available at FS:[0]  

	windows calls into a usermode exception dispatcher routine called kiUserExceptionDispatcher in NTDLL.dll, kiuserexceptiondispatcher calls int ortdispatchexception whihc is reponsible or going through the linked list at exceptionlist and looking for an exception handler that can deal with the exception.  

	the linked list is essentially a chain of _exception_registration_record datastructures  

	beyond the frame based exception handlers recent versions of the operating system also support vector of exception handlers, which is a linear list of handlers that are called for every execption regardless of whihc code generated it