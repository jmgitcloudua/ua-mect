#include <stdio.h>

void swap(int *p, int *q)
{
    int tmp;
    tmp = *p;
    *p = *q;
    *q = tmp;
}
// shell sort version 1.0
void shellSort(int seq[], unsigned int nelem)
{

    unsigned int i, increment, ntrocas;

    for (increment = nelem / 2; increment > 0; increment /= 2)
    {
        do
        {
            ntrocas = 0; // initialize the swap counter
            for (i = increment; i < nelem; i++)
            {
                if (seq[i - increment] > seq[i])
                {
                    swap(&seq[i], &seq[i - increment]); //change the elements
                    ntrocas++;                          //update the number of exchanges made
                }
            }

        } while (ntrocas);
    }
}
// shell sort version 2.0
void shellSort2(int seq[], unsigned int nelem)
{

    unsigned int i, j, increment, tmp;

    for (increment = nelem / 2; increment > 0; increment /= 2)
    {
        for (i = increment; i < nelem; i++)
        {
            tmp = seq[i]; // copy an element to sort
            for (j = i; j >= increment; j -= increment)
            {
                if (tmp < seq[j-increment])
                {
                    seq[j] = seq[j-increment]; //shift elements
                }
                else
                {
                    break;
                }
                
            }
            seq[j] = tmp; //insert the element to be sorted in the position
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
    shellSort(seq, nelem);
    printf("Sorted array (shell sort(v1)) : \n");
    printArray(seq, nelem);
    shellSort2(seq, nelem);
    printf("Sorted array (shell sort(v2)) : \n");
    printArray(seq, nelem);
    return 0;
}
