#include <stdio.h>
#include <stdlib.h>

int check_admin(unsigned int input);

int check_admin(unsigned int input)
{
	unsigned int admin = 0xdeadbeef;
	if (admin == input)
	{
		return 1;
	}
	
	return 0;
}

int main()
{
	unsigned int input;
	int result = 0;
	printf("Welcome, Enter Admin pin: ");
	scanf("%x", &input);
	result = check_admin(input);

	if (result == 1)
	{
		printf("\nyou're admin now!\n");
		exit(0);
	}
	printf("\ninvalid pin!, Your input: %x\n", input);
	return 0;
}
