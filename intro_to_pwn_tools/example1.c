#include <stdio.h>

int main() 
{
    char name[64];
    puts("What is your name?");
    scanf("%64s", name);
    printf("Hello %s\n", name);
    return 0;
}