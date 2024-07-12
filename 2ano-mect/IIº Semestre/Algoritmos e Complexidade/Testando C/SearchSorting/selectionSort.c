#include <stdio.h>

void swap(int *p, int *q)
{
    int tmp;
    tmp = *p;
    *p = *q;
    *q = tmp;
}
//selection sort verion 1.0
void selectionlSort(int seq[], unsigned int nelem)
{

    unsigned int i, j, indexMin;

    for (i = 0; i < nelem - 1; i++)
    {
        indexMin = i; //the smallest value is in position i
        for (j = i + 1; j < nelem; j++)
        {
            if (seq[indexMin] > seq[j])
            {
                indexMin = j; //the smallest value is in position j
            }
        }
        if (indexMin != i)
        {
            swap(&seq[i], &seq[indexMin]); //change the elements
        }
    }
}
//selection sort verion 2.0
void selectionlSort2(int seq[], unsigned int n)
{
    for (int i = n - 1; i > 0; i--)
    {
        int indexMax = 0;
        for (int j = 1; j <= i; j++)
        {
            if (seq[j] >= seq[indexMax])
            {
                indexMax = j;
            }
        }
        if (indexMax != i)
        {
            swap(&seq[indexMax], &seq[i]);
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
    selectionlSort(seq, nelem);
    printf("Sorted array (selection sort(v1)) : \n");
    printArray(seq, nelem);
    //------------------------------------
    selectionlSort2(seq, nelem);
    printf("Sorted array (selection sort(v2)) : \n");
    printArray(seq, nelem);
    return 0;
}
