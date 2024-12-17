//
// Very simple program to illustrate the nn_base module
//
//
// Armando J. Pinho (ap@ua.pt)
// IEETA / LASI / DETI / University of Aveiro
// 2023
//
#include <stdio.h>
#include "nn_base.h"

int main() {
	FILE *fp;
	nn_t* nn;
	unsigned I, H, O;

	// Load the neural network specification stored in file "nnet.net" and create
	// the respective neural network data structure
	if((fp = fopen("nnet.net", "r"))  == NULL) {
		fprintf(stderr, "Error: failed to open input nnet file\n");
		return 1;
	}

	load_header(fp, &I, &H, &O);
	nn = create_nn(I, H, O);
	load_weights(fp, nn);
	fclose(fp);

	// Access a file ("nnet.inp") with input vectors and process each one of them
	// using this neural network
	if((fp = fopen("nnet.inp", "r"))  == NULL) {
		fprintf(stderr, "Error: failed to open inp file\n");
		return 1;
	}

	while(load_input_vector(fp, nn) != 0) {
		go_forward(nn);
		print_input_and_output(nn);
	}

	fclose(fp);

	// Save the current neural network in the file "nnet-out.net"
	if((fp = fopen("nnet-out.net", "w"))  == NULL) {
		fprintf(stderr, "Error: failed to open output nnet file\n");
		return 1;
	}

	save_nn(fp, nn);
	fclose(fp);

	return 0;
}

