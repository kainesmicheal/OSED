#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char * what = "Hello, AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";

char * greet(char * who) {
	char buffer[128];
	int maxSize;
	printf("%p\n",buffer);
	maxSize = strlen(who);
	if (maxSize > (sizeof(buffer) - 1)) {
		maxSize = sizeof(buffer) - 1;
	}
//	printf("here\n");
	strcpy(buffer, what);
//	printf("after\n");
	strncpy(buffer + strlen(buffer), who, maxSize);

	return strdup(buffer);
}

int main(int argc, char ** argv) {
	char * ptr;
#ifdef NEWARCH
	if (argv[1]) {
		what = argv[1];
	}
#endif

	ptr = getenv("exp");
	if (NULL == ptr) {
		// if type of comparision prevents issues where you may acidentally type if(ptr = NULL) {}
		errx(1, "set the environment variable exp");
	}

	printf("%s\n", greet(ptr));
	return 0;
}

