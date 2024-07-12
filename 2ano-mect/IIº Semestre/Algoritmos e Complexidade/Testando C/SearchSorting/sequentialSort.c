#include <stdio.h>

void swap(int *p, int *q)
{
    int tmp;
    tmp = *p;
    *p = *q;
    *q = tmp;
}
void sequentialSort(int seq[], unsigned int nelem)
{

    unsigned int i, j;

    for (i = 0; i < nelem - 1; i++)
    {
        for (j = i + 1; j < nelem; j++)
        {
            if (seq[i] > seq[j])
            {
                swap(&seq[i], &seq[j]); //change the elements
            }
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
    sequentialSort(seq, nelem);
    printf("Sorted array (sequential sort) : \n");
    printArray(seq, nelem);
    return 0;
}
