#include <stdio.h>
#include <stdlib.h>

struct test {
        int a;
        int b;
        char c;
        char d;
        float e;
};

struct test1 {
	char val[32];
};

int main(int argc, char ** argv) {
        struct test * tp;
	struct test1 * tp1;

        tp = malloc(sizeof(struct test));
	tp1 = malloc(sizeof(struct test1));
	tp1->val[0] = 'A';
	tp1->val[1] = 'A';
	tp1->val[30] = 'B';
	tp1->val[31] = 'B';

	printf("size of test: %d\n",sizeof(tp));
        printf("sizeof test: %d\n",sizeof(struct test));
	printf("location of test: %p\n",tp);

	
	printf("size of test1: %d\n",sizeof(tp1));
        printf("sizeof test1: %d\n",sizeof(struct test1));
	printf("location of test1: %p\n",tp1);


        return 0;
}


