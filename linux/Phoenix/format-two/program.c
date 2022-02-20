#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int changeme;

void bounce(char * str) {
	printf(str);
}

int main(int argc, char ** argv) {
	char buf[256];
	printf("address %x\n",&changeme);	
	if (argc > 1) {
		memset(buf, 0, sizeof(buf));
		strncpy(buf, argv[1], sizeof(buf));
		bounce(buf);
	}

	if (changeme != 0) {
		puts("\nYou have changed me!\n");
	} else {
		puts("\nty again!\n");
	}

	exit(0);
}
