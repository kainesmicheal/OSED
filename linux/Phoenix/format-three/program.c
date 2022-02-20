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
	char buf[4096];
	
	printf("changeme is located at address %x\n",&changeme);

	if (read(0, buf, sizeof(buf) - 1) <= 0) {
		exit(1);
	}
	
	bounce(buf);

	if (changeme == 0x64457845) {
		puts("You have Changed me!!!\n");
	} else {
		printf("Current value in changeme 0x%08x, want 0x64457845\n", changeme);
	}
	
	exit(0);
}
