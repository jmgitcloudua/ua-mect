#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//
// Simple example of use of the qsort function from the standard library and of
// pointers to functions.
//

//
// Prototype of the qsort function (info taken from the man page of qsort):
//
// void qsort(void *base, size_t nmemb, size_t size,
//   int (*compar)(const void *, const void *));

// The comparison function must return an integer less than, equal to, or greater than
// zero if the first argument is considered to be respectively less than, equal to, or
// greater than the second. If two members compare as equal, their order in the sorted
// array is undefined.

int up(const void* a, const void* b) {
	return *((char *)a) > *((char *)b) ? 1 : -1;
}

int down(const void* a, const void* b) {
	return *((char *)a) < *((char *)b) ? 1 : -1;
}

int main() {
	char a[] = "This is a string";

	// Descending
	qsort(a, strlen(a), sizeof(char), down);
	printf("%s\n", a);

	// Ascending
	qsort(a, strlen(a), sizeof(char), up);
	printf("%s\n", a);

	return 0;
}

