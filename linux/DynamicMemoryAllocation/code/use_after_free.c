#include <stdio.h>
#include <stdlib.h>

typedef struct UAFME {
	void (* vulnfunc) ();
} UAFME;

void good() {
	printf("I am good! :)\n");
}

void bad() {
	printf("I am bad <3\n");
}

int main (int argc, char ** argv) {
	UAFME * malloc1 = malloc(sizeof(UAFME));
	malloc1->vulnfunc = good;
	malloc1->vulnfunc();

	free(malloc1);

	long * malloc2 = malloc(0);
	*malloc2 = (long) bad;
	malloc1->vulnfunc();
}
