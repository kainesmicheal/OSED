#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

struct heapStructure {
	int priority;
	char * name;
};

int main(int argc, char ** argv) {
	struct heapStructure * i1;
	struct heapStructure * i2;

	i1 = malloc(sizeof(struct heapStructure));
	i1->priority = 1;
	i1->name = malloc(8);

	i2 = malloc(sizeof(struct heapStructure));
	i2->priority = 2;
	i2->name = malloc(8);

	strcpy(i1->name, argv[1]);
	strcpy(i2->name, argv[2]);
	puts("test\n");
	printf("and that's a wrap floks!%d\n",i1->priority);
}

void winner() {
	puts("Congratulations, you have called me");
}
