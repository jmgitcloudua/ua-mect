#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//
// Prints powers of 2, using two approaches
//
int main(int ac, char* av[]) {

	// If the program is called with a wrong number of arguments, it prints a usage message
	if(ac != 2) {
		printf("Usage: %s integer\n", av[0]);
		return 1;
	}

	int n;

	printf("Powers of 2 using successive multiplication\n");
	int power = 1;
	for(n = 0 ; n < atoi(av[1]) ; n++) {
		printf("Power %d of 2 is: %d\n", n, power);
		power *= 2;
	}

	printf("\nPowers of 2 using a call to the math lib function \"pow()\"\n");
	for(n = 0 ; n < atoi(av[1]) ; n++) {
		printf("Power %d of 2 is: %.0f\n", n, pow(2, n));
	}

	return 0;
}
