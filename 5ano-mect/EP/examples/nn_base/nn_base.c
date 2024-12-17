//
// Implementation file for a simple module implementing a fully connected neural network
// with a single layer of hidden units. Note that the module is incomplete. For
// example, it misses the definition of the bias of the units and only implements
// a linear activation function.
//
// Armando J. Pinho (ap@ua.pt)
// IEETA / LASI / DETI / University of Aveiro
// 2023
//
#include <stdio.h>
#include <stdlib.h>
#include "nn_base.h"

//
// Creates a fully connected neural network with one hidden layer of units
// (two layers of weights, initialized to zero).
//
nn_t* create_nn(unsigned I, unsigned H, unsigned O) {
	nn_t* nn;

	if((nn = (nn_t*)malloc(sizeof(nn_t))) == NULL) {
		fprintf(stderr, "Error: memory allocation failure\n");
		exit(1);
	}

	nn->I = I; nn->H = H; nn->O = O;

	if((nn->inp = (double*)calloc(I, sizeof(double))) == NULL) {
		fprintf(stderr, "Error: memory allocation failure\n");
		exit(1);
	}

	if((nn->u_h = (unit_t*)calloc(H, sizeof(unit_t))) == NULL) {
		fprintf(stderr, "Error: memory allocation failure\n");
		exit(1);
	}

	if((nn->u_o = (unit_t*)calloc(O, sizeof(unit_t))) == NULL) {
		fprintf(stderr, "Error: memory allocation failure\n");
		exit(1);
	}

	if((nn->w_ih = (double**)calloc(I, sizeof(double*))) == NULL) {
		fprintf(stderr, "Error: memory allocation failure\n");
		exit(1);
	}

	for(unsigned i = 0 ; i < I ; i++)
		if((nn->w_ih[i] = (double*)calloc(H, sizeof(double))) == NULL) {
			fprintf(stderr, "Error: memory allocation failure\n");
			exit(1);
		}
	
	if((nn->w_ho = (double**)calloc(H, sizeof(double*))) == NULL) {
		fprintf(stderr, "Error: memory allocation failure\n");
		exit(1);
	}

	for(unsigned h = 0 ; h < H ; h++)
		if((nn->w_ho[h] = (double*)calloc(O, sizeof(double))) == NULL) {
			fprintf(stderr, "Error: memory allocation failure\n");
			exit(1);
		}
	
	return nn;
}

void load_header(FILE* fp, unsigned* I, unsigned* H, unsigned* O) {
	if(fscanf(fp, "%u %u %u", I, H, O) != 3) {
		fprintf(stderr, "Error: reading file header\n");
		exit(1);
	}
}

void load_weights(FILE* fp, nn_t* nn) {
	unsigned li, ui, lo, uo;
	double w;

	while(fscanf(fp, "%u:%u %u:%u %lf", &li, &ui, &lo, &uo, &w) == 5) {
		if(lo != li+1) {
			fprintf(stderr, "Error: connections only allowed between consecutive layers\n");
			exit(1);
		}

		switch(li) {
			case 1:
				nn->w_ih[ui-1][uo-1] = w;
				break;
			case 2:
				nn->w_ho[ui-1][uo-1] = w;
				break;
		}
	}
}

void save_nn(FILE* fp, nn_t* nn) {
	if(fprintf(fp, "%u %u %u\n", nn->I, nn->H, nn->O) < 0) {
		fprintf(stderr, "Error: writing file header\n");
		exit(1);
	}

	for(unsigned i = 0 ; i < nn->I ; i++)
		for(unsigned h = 0 ; h < nn->H ; h++)
			fprintf(fp, "1:%d 2:%d %f\n", i+1, h+1, nn->w_ih[i][h]);

	for(unsigned h = 0 ; h < nn->H ; h++)
		for(unsigned o = 0 ; o < nn->O ; o++)
			fprintf(fp, "2:%d 3:%d %f\n", h+1, o+1, nn->w_ho[h][o]);
}

unsigned load_input_vector(FILE* fp, nn_t* nn) {
	for(unsigned i = 0 ; i < nn->I ; i++)
		if(fscanf(fp, "%lf", &nn->inp[i]) != 1)
			return 0;

	return nn->I;
}

static double unit_activation(double inp) {
	return inp;
}

void go_forward(nn_t* nn) {
	// From input to hidden
	for(unsigned h = 0 ; h < nn->H ; h++) {
		nn->u_h[h].inp = 0;
		for(unsigned i = 0 ; i < nn->I ; i++)
			nn->u_h[h].inp += nn->inp[i] * nn->w_ih[i][h];

		nn->u_h[h].out = unit_activation(nn->u_h[h].inp);
	}

	// From hidden to output
	for(unsigned o = 0 ; o < nn->O ; o++) {
		nn->u_o[o].inp = 0;
		for(unsigned h = 0 ; h < nn->H ; h++)
			nn->u_o[o].inp += nn->u_h[h].out * nn->w_ho[h][o];

		nn->u_o[o].out = unit_activation(nn->u_o[o].inp);
	}
}

void print_input(nn_t* nn) {
	for(unsigned i = 0 ; i < nn->I ; i++)
		printf("%.3f ", nn->inp[i]);

	printf("\n");
}

void print_output(nn_t* nn) {
	for(unsigned o = 0 ; o < nn->O ; o++)
		printf("%.3f ", nn->u_o[o].out);

	printf("\n");
}

void print_input_and_output(nn_t* nn) {
	for(unsigned i = 0 ; i < nn->I ; i++)
		printf("%.3f ", nn->inp[i]);

	printf("-> ");
	for(unsigned o = 0 ; o < nn->O ; o++)
		printf("%.3f ", nn->u_o[o].out);

	printf("\n");
}

