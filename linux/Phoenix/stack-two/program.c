#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char ** argv) {
	struct {
		char buffer[64];
		volatile int changeme;
	} locals;

	char * ptr;

	ptr = getenv("exp");

	if (ptr == NULL) {
		errx(1, "Please set exp env variable.");
	}

	locals.changeme = 0;
	strcpy(locals.buffer, ptr);

	if (locals.changeme == 0x0d0a090a) {
		puts("Well done, you have changed the value");
	} else {
		printf("Almost! change me is 0x%08x, we want 0x0d0a09a\n", locals.changeme);
	}

	exit(0);
}
