#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char * gets(char *);

void start_level() {
	char buffer[128];
	gets(buffer);
}

int main() {
	start_level();

}
