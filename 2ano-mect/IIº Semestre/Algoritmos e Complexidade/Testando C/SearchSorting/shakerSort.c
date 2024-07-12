#include <stdio.h>

void swap(int *p, int *q)
{
    int tmp;
    tmp = *p;
    *p = *q;
    *q = tmp;
}

// shaker sort version 1.2
void shakerSort(int seq[], unsigned int nelem)
{

    unsigned int i, indexstart = 1, indexend = nelem - 1, utrocas;
    do
    {
        /*ascendent passage*/
        for (i = indexend; i >= indexstart; i--)
        {
            if (seq[i - 1] > seq[i])
            {
                swap(&seq[i], &seq[i - 1]); //change the elements
                utrocas = i;                //update the position of the last change
            }
            indexstart = utrocas + 1; // update the superior limit
        }
        /*descendent passage*/
        for (i = indexstart; i <= indexend; i++)
        {
            if (seq[i - 1] > seq[i])
            {
                swap(&seq[i], &seq[i - 1]); //change the elements
                utrocas = i;                //update the position of the last change
            }
            indexend = utrocas - 1; //update the inferior limit
        }

    } while (indexstart < indexend);
}
// shaker sort version 2.0
void shaker_sort(int a[], int n)
{
    int p, i;
    for (p = 1; p <= n / 2; p++)
    {
        for (i = p - 1; i < n - p; i++)
            if (a[i] > a[i+1])
                swap(&a[i], &a[i + 1]);
        for (i = n - p - 1; i >= p; i--)
            if (a[i] < a[i-1])
                swap(&a[i], &a[i - 1]);
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
    shaker_sort(seq, nelem);
    printf("Sorted array (shaker sort) : \n");
    printArray(seq, nelem);
    return 0;
}
