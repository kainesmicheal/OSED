#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void bounce(char * str) {
	printf(str);
	exit(0);
}

void congratulations() {
	printf("Well done, You're redirected to code execution!\n");
	exit(0);
}

int main(int argc, char ** argv) {
	char buf[4096];
	printf("buf %x\n",buf);
	if (read(0, buf, sizeof(buf) - 1) <= 0) {
		exit(1);
	}

	bounce(buf);
}
