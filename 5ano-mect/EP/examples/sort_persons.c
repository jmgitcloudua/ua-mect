#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//
// Example of sorting user-defined data types (structures)
//

typedef struct person {
	char* name;
	unsigned int age;
} PERSON;

//
// Comparison function for sorting by name
//
int up_name(const void* a, const void* b) {
    return strcmp(((PERSON *)a)->name, ((PERSON *)b)->name);
}

//
// Comparison function for sorting by age
//
int up_age(const void* a, const void* b) {
    return ((PERSON *)a)->age > ((PERSON *)b)->age ? 1 : -1;
}

int main() {
	PERSON persons[4] = {{"Maria", 12}, {"Manuel", 24}, {"Ana", 15}, {"Afonso", 34}};

	qsort(persons, 4, sizeof(PERSON), up_name);
	printf("Sorting by name...\n");
	for(int n = 0 ; n < 4 ; n++)
		printf("%s (%u)\n", persons[n].name, persons[n].age);

	qsort(persons, 4, sizeof(PERSON), up_age);
	printf("\nSorting by age...\n");
	for(int n = 0 ; n < 4 ; n++)
		printf("%s (%u)\n", persons[n].name, persons[n].age);

	return 0;
}

