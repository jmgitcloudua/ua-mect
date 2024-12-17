#include <stdio.h>
#include <stdlib.h>

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
	return *((int *)a) > *((int *)b) ? 1 : -1;
}

int down(const void* a, const void* b) {
	return *((int *)a) < *((int *)b) ? 1 : -1;
}

int main() {
	int a[10] = { 3, 5, 1, 10, -2, 12, -6, 0, 4, -8 };

	// Descending sorting
	qsort(a, 10, sizeof(int), down);
	for(int n = 0 ; n < 10 ; n++)
		printf("%d ", a[n]);

	printf("\n");

	// Ascending sorting
	qsort(a, 10, sizeof(int), up);
	for(int n = 0 ; n < 10 ; n++)
		printf("%d ", a[n]);

	printf("\n");

	return 0;
}

