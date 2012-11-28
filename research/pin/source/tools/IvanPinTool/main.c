#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_LENGTH 8

char* helloworld()
{
	char first[BUFFER_LENGTH];
	char second[BUFFER_LENGTH];
	char* p; 
	int x;

	printf("Enter first name: \n");
	fgets (first, BUFFER_LENGTH, stdin);
	x = strlen (first) - 1;
	if (first[x] == '\n') 
		first[x] = '\0';

	printf("Enter last name: \n");
	fgets (second, 64, stdin); //Note can cause seg fault.
	x = strlen (second) - 1;
	if (second[x] == '\n') 
		second[x] = '\0';

	printf("Hello: %s %s\n", first, second);

	return p;
}

int main()
{
	helloworld();

	return 0;
}
