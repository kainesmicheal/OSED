#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char * gets(char *);

void magic_function() {
	printf("Congratulations, you have found me!\n");
	exit(0);
}

void start_level() {
	char buffer[64];
	void * ret;

	gets(buffer);

	ret = __builtin_return_address(0);
	printf("and will be returing to %p\n", ret);
}

int main(int argc, char ** argv) {
	start_level();
	return 0;
}
