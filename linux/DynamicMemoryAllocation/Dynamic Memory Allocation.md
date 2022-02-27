![[Pasted image 20220227060707.png]]

malloc:

gives a  number of bytes, request a piece of memory at least that size. Return value is pointer to that area.

free:

given a pointer returned by malloc, mark that area unallocated

![[Pasted image 20220227061132.png]]

a block of memory represents whole block size + payload + padding

system calls used by malloc

sbrk - increase or decrease brk pointer, it acts as the boundary between legal and illegal pages
mmap - this maps a random usable memory of given length

malloc uses both of this to get the best performance

cat proc/processid/maps

give all the information abouut the memory like heap , stackk and all dynamic memory 

The first thing worth mentioning is that not all addresses returned by malloc reside in what we call the heap

![[Pasted image 20220227073236.png]]

malloc has 2 ways of allocating memory

on the heap 

-> a memory region in continuation of the .data which can be resized with the brk() and sbrk() system calls for small sizes (default is < 128 kb)

in the mmap region

-> above the stack and shared library zones generally, done using mmap() system call for larger sizes (default is > 128kb)

The internal realse size can be get using 

```
void* ptr = malloc(100);
unsigned long size = ((unsigned long*)ptr)[-1] & ~7;
```

& ~7 is added to 0 out the last 3 bits which are acutally flags and not part of the size

![[Pasted image 20220227074102.png]]

![[Pasted image 20220227072612.png]]


allocated memory for all ptrs are of 32bytes even tho we have specified differrent size

and rest of the space is padded with zeros

even the malloc with 0 is also assigned with 32 bytes which is the minimum size (16 for 32-bit and 32 for 64-bit).

![[Pasted image 20220227072639.png]]

the block contains the size first, here in our case each of the bock is of size 32 which is hex 20, 

but it is mentioned as 21, because the last bit is set to represent that this space is allocated using mmap

When allocating on the heap malloc uses various other methods of allocating small data regions (arena based allocation with multiple bins of different sizes)

![[Pasted image 20220227074632.png]]

When two threads call malloc at the same time memory is allocated immediatly since each thread maintains a seperate heap segment and hence free list data structure maintaining those heaps are also seperate. this act of maintaining separate heap and freelist data structures for each thread is called per thread arena


![[Pasted image 20220227083835.png]]

Initially a heap of size 132kb is allocated even tho we only called malloc with 1000 bytes, this contiguous region of heap memory is called arean, as it was created for main function its called main arena.

futher allocations requests keeps using this arena untill it runs of of free space.

when arena runs out of free space, it can grow by increasing tthe break location, after growing top chunks size is adjusted to include the extra space

similarly arena can also shrink when there is lot of free space on top chunk

when allocated memory region is freed, memory behind it doesnt get released to the operating system immediatly. allocated memory region (of size 1000 bytes) is released only to lib. which adds this freed block to main arenas bin (in glibc malloc, freelist datastructures are referred as bins)

later when user requests memory glibc malloc doesnt get new heap memory from kernel, instead it will try to find a free block in bin. and only when no free block exists, it obtains memory from kernel

![[Pasted image 20220227085048.png]]

heap segment is created for thread1, region 7ffff0000000-7ffff0021000, its not in heap location hence created using mmap(), even though we request 1000bytes we get 132kb. this is called the thread arena

An insance application can run more number of threads in such case having one arena per thread becomes bit expensive and useless, hence arena limit is based on the number of cores persent in the system

![[Pasted image 20220227085452.png]]

Chunk Types:

Allocated chunk
Free chunk
Top chunk
Last Remainder chunk

![[Pasted image 20220227090148.png]]

![[Pasted image 20220227090421.png]]

![[Pasted image 20220227090828.png]]

![[Pasted image 20220227090907.png]]

Bins:

Bins are the freelist datastructures. They are used to hold free chunks. Based on chunk sizes, different bins are available.

Fast bin
Unsorted bin
Small bin
Large bin

fastbinsY: This array hold fast bin

bins: This array hold unsorted, small and large bins. Totally there are 126 bins and its divided as follows:
	Bin 1 - Unsorted bin
	Bin 2 to Bin 63 - Small bin
	Bin 64 to bin 126 - Large bin


contine here

https://sploitfun.wordpress.com/2015/02/10/understanding-glibc-malloc/

https://ocw.cs.pub.ro/courses/cns/labs/lab-10

https://sensepost.com/blog/2017/linux-heap-exploitation-intro-series-used-and-abused-use-after-free/