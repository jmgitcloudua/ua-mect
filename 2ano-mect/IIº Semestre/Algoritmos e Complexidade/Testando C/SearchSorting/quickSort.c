#include <stdio.h>

void swap(int *p, int *q)
{
    int tmp;
    tmp = *p;
    *p = *q;
    *q = tmp;
}

// quick sort sort verion 1.0
void quickSort(int seq[], unsigned int start, unsigned int end)
{
    unsigned int medio, nelem = end - start + 1, indi, indj;
    if (nelem <= 1)
        return;     /* pivot index calculation */
    if (nelem == 2) /*put the ends and the pivot in ascending order */
    {
        if (seq[start] > seq[end])
            swap(&seq[start], &seq[end]);
        return;
    }
    medio = (start + end) / 2; /* c·lculo do Ìndice do pivot */
                                /* colocar os extremos e o pivot por ordem crescente */
    if (seq[start] > seq[medio])
        swap(&seq[start], &seq[medio]);
    if (seq[start] > seq[end])
        swap(&seq[start], &seq[end]);
    if (seq[medio] > seq[end])
        swap(&seq[medio], &seq[end]);
    /* if the aggregate only has 3 elements, then it is already · ordered */
    if (nelem == 3)
        return;
    /* hide the pivot in the penultimate position of the aggregate */
    swap(&seq[medio], &seq[end - 1]);
    indi = start;
    medio = indj = end - 1;
    for (;;)
    {
        /* look for elements on the left larger than pivot */
        while (seq[++indi] < seq[medio])
            ;
        /* look for elements in the right part smaller than pivot */
        while (seq[--indj] > seq[medio])
            ;
        if (indi < indj)
            swap(&seq[indi], &seq[indj]);
        else
            break;
    }
    /* retrieve the pivot to the average position of the aggregate */
    medio = indi;
    swap(&seq[medio], &seq[end - 1]);
    /* recursive invocation to the left part of the aggregate */
    quickSort(seq, start, medio - 1);
    /* recursive invocation to the right part of the aggregate */
    quickSort(seq, medio + 1, end);
}
// quick sort sort verion 2.0
/*void quickSort2(int seq[], unsigned int n)
{
   
    
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
    quickSort(seq, 0, nelem-1);
    printf("Sorted array (quick sort(v1)) : \n");
    printArray(seq, nelem);
    //---------------------------
    /*quickSort2(seq, nelem);
    printf("Sorted array (bubble sort(v2)) : \n");
    printArray(seq, nelem);*/
    return 0;
}
