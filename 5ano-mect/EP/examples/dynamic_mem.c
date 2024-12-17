#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//
// This program receives a string in the command line and creates a copy of it
// using dynamic memory allocation
//
int main(int argc, char* argv[]) {

	if(argc != 2) {
		fprintf(stderr, "Usage: %s string\n", argv[0]);
		return 1;
	}

	// Request a segment of memory of size equal to the length of the string, plus one
	// for storing the '\0' string terminator
	char* copy = malloc(strlen(argv[1]) + 1);

	// Check if the memory address is valid
	if(copy == NULL) {
		fprintf(stderr, "Error: failed memory allocation\n");
		return 1;
	}

	// Do the copy
	int n;
	for(n = 0 ; argv[1][n] != '\0' ; n++)
		copy[n] = argv[1][n];

	copy[n] = '\0';

	// Change the first character of the copy
	copy[0] = '!';

	printf("The copy now has: %s\n", copy);
	printf("The original stays unchanged: %s\n", argv[1]);

	return 0;
}
