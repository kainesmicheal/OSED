#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char * gets(char *);

int main(int argc, char ** argv) {
	struct {
		char buffer[64];
		volatile int changeme;
	} locals;

	locals.changeme = 0;
	gets(locals.buffer);

	if (locals.changeme != 0) {
		printf("changeme: %d\n",locals.changeme);
		puts("Well done, the 'changeme' variable has been changed!");
	} else {
		printf("changeme: %d\n",locals.changeme);
		puts("uh oh, 'changeme' has not yet benn changed. try again.");
	}

	exit(0);
}
