#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main() {
	void * malloc_ptr;
	void * ptr1, * ptr2, * ptr3, * ptr4, * ptr5;
	malloc_ptr = malloc(1024);
	ptr1 = malloc(sizeof(int) * 4);
//	printf("Size: %d\n", ((unsigned long *) ptr1)[-1] & ~7);
	memset(ptr1, 'A', 4 * sizeof(int));
	ptr2 = malloc(sizeof(int) * 5);
//	printf("Size: %d\n", ((unsigned long *) ptr2)[-1] & ~7);
	memset(ptr2, 'B', 5 * sizeof(int));
	ptr3 = malloc(sizeof(int) * 6);
//	printf("Size: %d\n", ((unsigned long *) ptr3)[-1] & ~7);
	memset(ptr3, 'C', 6 * sizeof(int));
	ptr4 = malloc(sizeof(int) * 2);
//	printf("Size: %d\n", ((unsigned long *) ptr4)[-1] & ~7);
	memset(ptr4, 'D', 2 * sizeof(int));
	ptr5 = malloc(0);
//	printf("Size: %d\n", ((unsigned long *) ptr5)[-1] & ~7);

	return 0;
}
