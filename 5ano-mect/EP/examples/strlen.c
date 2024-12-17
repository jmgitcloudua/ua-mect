#include <stdio.h>
#include <stdlib.h>

//
// This program prints the number of characters of a string passed in the command line
// Note: it does not use, intentionally, the "strlen()" function...
//
int main(int ac, char* av[]) {

	// If the program is called with a wrong number of arguments, it prints a usage message
	if(ac != 2) {
		printf("Usage: %s string\n", av[0]);
		return 1;
	}

	// Goes through the string until it reaches the null ('\0') character
	int n;
	for(n = 0 ; av[1][n] != '\0' ; n++)
		;

	printf("String has %d characters\n", n);

	return 0;
}