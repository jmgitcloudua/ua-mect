#include <stdio.h>

//
// This program copies orig_file into dest_file
//
int main(int argc, char* argv[]) {
	FILE* fp_in;
	FILE* fp_out;

	if(argc != 3) {
		printf("Usage: %s orig_file dest_file\n", argv[0]);
		return 1;
	}

	if((fp_in = fopen(argv[1], "rb")) == NULL) {
		fprintf(stderr, "Error: cannot open file \"%s\"\n", argv[1]);
		return 1;
	}

	if((fp_out = fopen(argv[2], "wb")) == NULL) {
		fprintf(stderr, "Error: cannot open file \"%s\"\n", argv[2]);
		return 1;
	}

	int c;
	while((c = getc(fp_in)) != EOF)
		putc(c, fp_out);

	fclose(fp_in);
	fclose(fp_out);

	return 0;
}