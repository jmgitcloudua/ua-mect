//
// Header file for a small example illustrating the notions of modules and structs
//
#ifndef COMPLEX_H
#define COMPLEX_H

typedef struct complex {
	double real;
	double imag;
} Complex;

Complex mult_complex(Complex a, Complex b);
Complex add_complex(Complex a, Complex b);

#endif
