#include <stdio.h>

/*void swap(int *p, int *q)
{
    int tmp;
    tmp = *p;
    *p = *q;
    *q = tmp;
}*/

// insertion sort verion 1.0
void insertionSort(int seq[], unsigned int nelem)
{

    unsigned int i, j, tmp;
    for (i = 1; i < nelem; i++)
    {
        tmp = seq[i]; // copy the element to sort

        /* shitf the elements behind him that are major*/
        for (j = i; j > 0 && seq[j-1] > tmp; j--)
        {
            seq[j] = seq[j-1];
        }
        seq[j] = tmp; //insert the element to sort in position
            
    }
    
}
// insertion sort verion 2.0
void insertElement(int sorted[], int n, int nelem){
    //sorted is sorted
    // there is space to add more than an element
    int i;
    for ( i = n - 1; (i >= 0) && (nelem < sorted[i]); i--)
    {
        sorted[i+1] = sorted[i];
    }
    sorted[i+1] = nelem;
}
void insertionSort2(int a[], int n){
    
    for (int i = 1; i < n; i++)
    {
        if (a[i] < a[i-1])
        {
            insertElement(a,i,a[i]);
        }
        
    }
    
}
void printArray(int seq[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf(" %d ", seq[i]);
    }
    printf("\n");
}
int main(int argc, char const *argv[])
{
    int seq[] = {4, 2, 8, 100, 40, 80, 120, 220, 16, 10};
    unsigned int nelem = sizeof(seq) / sizeof(*seq);
    printf("Array not Sorted : \n");
    printArray(seq, nelem);
    insertionSort(seq, nelem);
    printf("Sorted array (insertion sort(v1)) : \n");
    printArray(seq, nelem);
    //-------------------------------------
    insertionSort2(seq, nelem);
    printf("Sorted array (insertion sort(v2)) : \n");
    printArray(seq, nelem);
    return 0;
}
