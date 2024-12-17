#include <stdio.h>

//
// Simple illustration of arrays, pointers and pointer arithmetic
//
int main() {
	int a[10] = { 0 }; // creates an array of 10 integers, initialized to zero
	int* ptr_to_int; // creates a pointer to int;

	a[5] = 1000;
	ptr_to_int = &a[5]; // ptr_to_int now holds the memory address of the 6th position
					    // of the array. Note that the 1st element is a[0]
	printf("The address of a[5] is %p\n", ptr_to_int);
	printf("(a + 5) is also %p\n", a + 5); // the name of an array is also the address of
										   // its first element

	printf("The value of a[5] is %d\n", a[5]);
	printf("The value of *(a + 5) is also %d\n", *(a + 5));
	printf("Which is the same as *ptr_to_int: %d\n", *ptr_to_int);

	return 0;
}
