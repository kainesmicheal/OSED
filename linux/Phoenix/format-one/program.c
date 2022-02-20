#include <err.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>


int main(int argc, char ** argv) {
	struct {
		char dest[32];
		volatile int changeme;
	} locals;

	char buffer[16];

	if ( fgets(buffer, sizeof(buffer) - 1, stdin) == NULL) {
		errx(1, "Unable to get buffer");
	}

	buffer[15] = 0;
	printf("%x\n", buffer);
	sprintf(locals.dest, buffer);

	if (locals.changeme != 0x45764f6c) {
		printf("current value is 0x%08x\n", locals.changeme);
	} else {
		puts("You have changed me, congrats");
	}

	exit(0);
}

