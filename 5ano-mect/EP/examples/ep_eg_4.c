#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void swap(int *a, int *b);
void sequentialSort(int *arr, int size);
int up(const void *a, const void *b);
int down(const void *a, const void *b);

// struct of PERSON
typedef struct person
{
    char * name;
    unsigned int age;
} PERSON;

int up_name(const void *a, const void *b);
int up_age(const void *a, const void *b);

int main(){
    int a = 10, b = 20;
    printf("Before swap: a = %d, b = %d\n", a, b);
    swap(&a, &b);
    printf("After swap: a = %d, b = %d\n", a, b);
    puts("==============Sequential Sort==============");
    int arr[] = {1, 5, 3, 2, -100, 9, 500, 4};
    int size = sizeof(arr) / sizeof(arr[0]);
    sequentialSort(arr, size);
    for(int i = 0; i < size; i++){
        printf("%d ", arr[i]);
    }
    puts("\n");

    puts("==============Ascending QSort==============");
    int arr2[] = {1, 5, 3, 2, -8, -100, 600, 4};
    int size2 = sizeof(arr2) / sizeof(arr2[0]);
    qsort(arr2, size2, sizeof(int), up);
    for(int i = 0; i < size2; i++){
        printf("%d ", arr2[i]);
    }
    puts("\n");

    puts("==============Descending QSort==============");
    int arr3[] = {1, 5, 3, 2, -8, -100, 600, 4};
    int size3 = sizeof(arr3) / sizeof(arr3[0]);
    qsort(arr3, size3, sizeof(int), down);
    for(int i = 0; i < size3; i++){
        printf("%d ", arr3[i]);
    }

    puts("\n==============Sorting by Name==============");
    PERSON people[] = {
        {"John", 20},
        {"Jane", 21},
        {"Adam", 19},
        {"Rachel", 18},
        {"Zoe", 22},
        {"David", 23},
        {"Paul", 24},
        {"Peter", 25},
        {"Mary", 26},
        {"Mark", 27},
        {"Luke", 28},
        {"Matthew", 29},
        {"James", 30},
        {"John", 31},
        {"Bia", 32},
    };
    int size4 = sizeof(people) / sizeof(people[0]);
    qsort(people, size4, sizeof(PERSON), up_name);
    for(int i = 0; i < size4; i++){
        printf("%s %d\n", people[i].name, people[i].age);
    }
    puts("\n==============Sorting by Age==============");
    qsort(people, size4, sizeof(PERSON), up_age);
    for(int i = 0; i < size4; i++){
        printf("%s %d\n", people[i].name, people[i].age);
    }

    puts("\n");



    return 0;
}

// swap two numbers
void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}
// up two numbers
int up(const void *a, const void *b){
    return *(int *)a - *(int *)b;
}
// down two numbers
int down(const void *a, const void *b){
    return *(int *)b - *(int *)a;
}
// Comparison function for sorting by name
int up_name(const void *a, const void *b){
    return strcmp(((PERSON *)a)->name, ((PERSON *)b)->name);
}
// Comparison function for sorting by age
int up_age(const void *a, const void *b){
    return ((PERSON *)a)->age - ((PERSON *)b)->age;
}

//sequential sort
void sequentialSort(int *arr, int size){
    for(int i = 0; i < size; i++){
        for(int j = i + 1; j < size; j++){
            if(arr[i] > arr[j]){
                swap(&arr[i], &arr[j]);
            }
        }
    }
}
//