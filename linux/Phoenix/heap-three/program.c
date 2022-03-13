#include <stdio.h>
#include "malloc.c"
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

void winner() {
	puts("won\n");
}

int main(int argc, char ** argv) {
	char * a, * b, * c;
	a = malloc(32);
	b = malloc(32);
	c = malloc(32);

	strcpy(a, argv[1]);
	strcpy(b, argv[2]);
	strcpy(c, argv[3]);

	free(c);
	free(b);
	free(a);

	puts("Dynamite failed?\n");
}
