#include <stdio.h>
#include <stdlib.h>

// merge sort verion 1.0
void MergeListSort(int seq[], unsigned int start, unsigned int middle, unsigned int end)
{
    unsigned int inica = start, inicb = middle + 1, indi = 0, indc;
     /*Memory attribution to household */
    int *seqtemp = (int *)calloc(end - start + 1, sizeof(int));
    while (inica <= middle && inicb <= end)
        if (seq[inica] < seq[inicb])
            seqtemp[indi++] = seq[inica++]; //element of the first part
        else
            seqtemp[indi++] = seq[inicb++]; //element of the second part
    /*Copy the rest elements of the first part of the array*/                                 
    while (inica <= middle)
        seqtemp[indi++] = seq[inica++];
    /*Copy the rest elements of the second part of the array*/
    while (inicb <= end)
        seqtemp[indi++] = seq[inicb++];
       /*Copy the result to sort the array*/
    for (indc = 0, inica = start; indc < indi; indc++, inica++)
        seq[inica] = seqtemp[indc];
    free(seqtemp); // freeing the local household memory
}
void MergeSort(int seq[], unsigned int start, unsigned int end)
{
    unsigned int middle;
    if (start < end) /* stop condition */
    {
        middle = (start + end) / 2; /* divide array */
        /* recursive call to sort the first half array*/
        MergeSort(seq, start, middle);
      /* recursive call to sort the second half array*/
        MergeSort(seq, middle + 1, end);
        /*merge the two of half sorted arrat*/
        MergeListSort(seq, start, middle, end);
    }
}
// merge sort verion 2.0
/*void mergeSort2(int a[], int n){
    
    for (int i = 1; i < n; i++)
    {
        if (a[i] < a[i-1])
        {
            insertElement(a,i,a[i]);
        }
        
    }
    
}*/


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
    MergeSort(seq, 0, nelem - 1);
    printf("Sorted array (merge sort(v1)) : \n");
    printArray(seq, nelem);
    //-------------------------------------
    /*insertionSort2(seq, nelem);
    printf("Sorted array (insertion sort(v2)) : \n");
    printArray(seq, nelem);*/
    return 0;
}
