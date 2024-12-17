//
// Header file for a simple module implementing a fully connected neural network
// with a single layer of hidden units. Note that the module is incomplete. For
// example, it misses the definition of the bias of the units and only implements
// a linear activation function.
//
// Armando J. Pinho (ap@ua.pt)
// IEETA / LASI / DETI / University of Aveiro
// 2023
//
#ifndef NN_BASE_H
#define NN_BASE_H

#include <stdio.h>

typedef struct unit {
	double	inp;  // dot product between the unit inputs and the corresponding weights
	double	out;  // unit_activation(inp)
} unit_t;

typedef struct nn {
	unsigned	I, H, O; // the number of inputs, hidden layer units and output units
	double*		inp;     // the inputs of the neural network
	unit_t*		u_h;     // the hidden layer
	unit_t*		u_o;     // the output layer
	double**	w_ih;    // weights from the input to the hidden layer
	double**	w_ho;    // weights from the hidden layer to the output layer
} nn_t;

nn_t* create_nn(unsigned I, unsigned H, unsigned O);
void load_header(FILE* fp, unsigned* I, unsigned* H, unsigned* O);
void load_weights(FILE* fp, nn_t* nn);
void save_nn(FILE* fp, nn_t* nn);
unsigned load_input_vector(FILE* fp, nn_t* nn);
void go_forward(nn_t* nn);
void print_input(nn_t* nn);
void print_output(nn_t* nn);
void print_input_and_output(nn_t* nn);

#endif

