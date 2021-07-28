Every program is given 32bits of memory space that is 2^32 which is 4GB  
  
address range is 0x00000000 to 0xffffffff  
  
direct access of physical memory also causes holes in address spaces, makes the memory unusable  
  
like if we have 4gp ram,, if two programs are accessing it with  
  
1st program -> 1gp  
2nd program -> 2gp  
  
now if the 1st prgram ends we will have 2 gp ram space  
  
but if a program that needs 2 gp ram comes , it wont be able to get a place , as the 2gp free memory in ram is splitted  
  
  
![[Pasted image 20210728151448.png]]
  
  
when two programs try to read or write the same physical address, it will cause crash  
  

  
  
To solve these issue we use Virtual memory, each program is given is own 32 bits virtual memory space  
  
each programs memory space is then mapped to Physical RAM memory space

##explanation

     
	Virtual memory takes program addresses and maps them to RAM addresses  

	because we have the mapper, we can move the oldest data into the harddisk and switch it when someone access it(Its costly but it provides a way)  

	Each program has its own mapper thus even the holes in memory can be used as mapper can map the address properly.  

	This also allows us to intentially map address for two programs to same physicall address to share data(in this case, we want to share data so its good)
	
![[Pasted image 20210728151545.png]]

![[Pasted image 20210728151609.png]]

![[Pasted image 20210728151639.png]]

##Working

    the program makes a call to translation which has the mapping table  
  

  ![[Pasted image 20210728151741.png]]

	if the data is in disk, then the data is moved back to the ram and the table value is updated respectively
	
##page tables


	Mapping and keeping track every virtual address to physical itself will cost a lot of memory  

	1 for every word = 1 billion entries (1GP)  

	so we map chunks of memory and chunk size is optionall (the tradeoff is the if we increase the page size we need find a simlar chunk to be able to map)  

	every chunk is called as a page  

	if we use chunk size as 4kb then  

	we only need 1 million entries  

	every chunk is mapped to chunk in the physical memory and single memory read is calucted based on the offset  

	for 4k page  

	our offset will be log2(4*2^10)  

	offset bits are not gonna change so we dont have store in it in the map table  

	rest of the bit are labled as page no, thus we have translate from virtual page number mapped to physical page number , after finding the mapped address offset is added to it.  
  
  
  
![[Pasted image 20210728151840.png]]

![[Pasted image 20210728151900.png]]

![[Pasted image 20210728151921.png]]


##Page faults

    We we hit a page that is in disk then it is a page fault  
  
	CPU generates a page fault exception  

	The os chooses a page to remove from the RAM and write it to disk  

	if the page is dirty, it need to be written back to disk first, if there is already of copy of it in disk which is not dirty then no need to write it again  

	and then the page number mapping is updated in the table
	
##calculation

![[Pasted image 20210728152011.png]]

##memory && TLB

    Only the mapped data can be accessed so both programs share same memory, but cant access eachothers data, unless we share the mapping  
  
	kernal space is not allowed for anyone.  

	there is random offset seperating the locations thus, we will never exacatly twhere the stack or heap will be placed for security reasons  

  
  ![[Pasted image 20210728152120.png]] 
  
	To make the lookup fast we use Translation Lookaside Buffre(TLB)  
  
![[Pasted image 20210728152142.png]]

##mulit-level page tables

    For 32 bit machine with 4kb pages we need  
  
	→ 1Million page table entries (2^20 = 1M)  
	→ Each PTE is about 4 bytes  
	→ 4MB in total  


	except each program needs its own page table:  

	if we have 100 programs running we need 400mb of page tables  

	we cant swap that page tables out to disk  
	if the page table is not in RAM, we have no way to access to it to find it  

	we can use multi level page tables to make the swapping possible
	
![[Pasted image 20210728152240.png]]

     
	we have one table which hold other tables, each table has 4kb of entries,  

	thus we can always have our 1st level table in memory which points to the other tables  

	other page that is pointed by the 1stlevel table can be switched whenever needed  

	thus only 4kb+ 4kb of data is located in hte memory per application instead of 4mb per application without multilevel paging
	
![[Pasted image 20210728152327.png]]

     
	we will devide the virtual page number into two  

	first 10 bits for the 1st level table and rest of 10 bits to 2nd level tabls
	
![[Pasted image 20210728152359.png]]

##TLB and caches

![[Pasted image 20210728152533.png]]

![[Pasted image 20210728152557.png]]

    if physical addr from TLB and physical tag matches then it is a proper hit 
	
	both are done parallely

