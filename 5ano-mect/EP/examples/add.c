#include <stdio.h>
#include <stdlib.h>

//
// This program prints the sum of two integers, passed in the command line
// If only one integer is passed, the other is assumed to be zero
//
// Note: the atoi() function does not distinguish between a valid zero value and a
// conversion error. Run "man atoi" in the command line to have more info about it
//
int main(int ac, char* av[]) {

	switch(ac) {
		case 2:
			// Only one integer is passed (the second is considered zero)
			printf("The sum is %d\n", atoi(av[1]));
			break;

		case 3:
			// Two integers are passed (their sum is printed)
			printf("The sum is %d\n", atoi(av[1]) + atoi(av[2]));
			break;

		default:
			// Invalid number of input arguments (a usage message is printed)
			printf("Usage: %s integer integer\n", av[0]);
			return 1;
	}

	return 0;
}