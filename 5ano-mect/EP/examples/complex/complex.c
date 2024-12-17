//
// Functions for a small example illustrating the notions of modules and structs
//
#include "complex.h"

//
// Multiplies to complex numbers
//
Complex mult_complex(Complex a, Complex b) {
	Complex product;

	product.real = a.real * b.real - a.imag * b.imag;
	product.imag = a.real * b.imag + a.imag * b.real;

	return product;
}

//
// Adds to complex numbers
//
Complex add_complex(Complex a, Complex b) {
	Complex sum;

	sum.real = a.real + b.real;
	sum.imag = a.imag + b.imag;

	return sum;
}

