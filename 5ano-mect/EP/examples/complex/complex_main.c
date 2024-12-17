//
// Small program for illustrating the use of the "complex" module
//
#include <stdio.h>
#include "complex.h"

int main() {
	Complex a = { 10, 20 }; // Definition and initialization 
	Complex b, x, y;

	b.real = 30; b.imag = 40; // Initialization after definition

	x = add_complex(a, b);
	y = mult_complex(a, b);

	printf("The addition is %g + %gi\n", x.real, x.imag);
	printf("The multiplication is %g + %gi\n", y.real, y.imag);
	return 0;
}

