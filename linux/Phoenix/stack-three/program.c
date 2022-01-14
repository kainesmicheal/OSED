#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void magic_function() {
	printf("Congratulations, you've have found me\n");
	exit(0);
}

int main(int argc, char ** argv) {
	struct {
		char buffer[64];
		volatile int (*fp)();
	} locals;

	locals.fp = NULL;
	gets(locals.buffer);

	if (locals.fp) {
		printf("calling function pointer @ %p\n", locals.fp);
		fflush(stdout);
		locals.fp();
	} else {
		printf("Function pointer remains unmodified, try again!\n");
	}

	exit(0);
}
