#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main() {
	char stack_buffer[44];
	char *finalinput;
	FILE *stream;

	finalinput = (char *)malloc(0x171);
	stream = fopen("flag.txt", "r");
	fgets(stack_buffer, 0x2c, stream);
	printf("%s\n", stack_buffer);
	return 0;
}
