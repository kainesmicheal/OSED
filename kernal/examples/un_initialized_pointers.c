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
