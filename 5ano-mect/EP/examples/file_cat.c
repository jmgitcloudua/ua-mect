#include <stdio.h>

//
// This program sends the content of a file to the standard output
//
int main(int argc, char* argv[]) {
	FILE *fp;

	if(argc != 2) {
		fprintf(stderr, "Usage: %s file_name\n", argv[0]);
		return 1;
	}

	if((fp = fopen(argv[1], "r")) == NULL) {
		fprintf(stderr, "Error: failed to open file\n");
		return 1;
	}

	int c;
	while((c = getc(fp)) != EOF)
		putc(c, stdout);

	return 0;
}