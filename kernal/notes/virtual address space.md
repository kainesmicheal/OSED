the virtual address space is usually larger than the phsical range from 0 to 2^n-1


All operating systems divide the physical address range in fixed size chunks called page frames

the virtual address range in equally sided chunks called pages.

Anytime a process needs to use a memory page, the virtual memory subsystem allocates a physical frame for it.

the translation from physical frames to virtual pages is done through page tables, which tell to which specific physical page frame a given virutal address maps.

once all the physical page frames have been allocated and a new one is needed, the os picks a page that is not being used and copies it to the disk, in the dedicated area called swap space, thereby freeing a physical frame that will be returned to the process.

This operation is called swapping

since accessing the hard drive is a slow operation, to improve performance the virtual memory subsystem first creates a virtual addres range for the process and then assigns a physical page frame only when that address is referenced for the first time.

this approcah is called demand paging

eg:

to get all the virtual memory address ranges a process  requested

`cat /proc/<pid>/maps`

![[Pasted image 20220806063653.png]]

rwxp as read/write/execute/private - for the page protections

the inner core of the CPU needs to address physical memory, exploit writers will neearly always play with virtual memory

page table is a datastructure

differennt page table is created for each process, and at each context switch the correct one is loaded.

Depending on the implementaiton, we have two possible scenarios

kernel space on behalf of user space or sparated kernel and user address space


![[Pasted image 20220806065452.png]]


Execution Context

anytime the cpu is in superviosr mode, the execution is said to be in interrupt context if no backing process is associtaed with it

Interrupt context is when a hardware interrupt accours and the cpu switches to interrupt service routine

the code in interrupt context cant block the execution, that is make a request to page that is not referenced yet, as the scheduler wont have any idea of pausing this and waking it up

Process context is when the kernel path is associated with process, that is through a system call

![[Pasted image 20220806071014.png]]


