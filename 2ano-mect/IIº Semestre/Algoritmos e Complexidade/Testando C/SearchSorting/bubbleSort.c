#include <stdio.h>

void swap(int *p, int *q)
{
    int tmp;
    tmp = *p;
    *p = *q;
    *q = tmp;
}

// bubble sort verion 1.0
void bubbleSort(int seq[], unsigned int nelem)
{

    unsigned int i, indexInitial, ntrocas;
    indexInitial = 1; // initialize the upper sort limit

    do
    {
        ntrocas = 0; // initialize the swap counter
        for (i = nelem - 1; i >= indexInitial; i--)
        {
            if (seq[i-1] > seq[i])
            {
                swap(&seq[i], &seq[i-1]); //change the elements
                ntrocas++;//update the number of exchanges made
            }
            
        }
        indexInitial++; //update the upper sort limit
        
    } while (ntrocas && indexInitial < nelem);     
    
}
// bubble sort verion 2.0
void bubbleSort2(int seq[], unsigned int n)
{
   unsigned int k = n; int stop = 0;
   while (stop == 0)
   {
       stop = 1; k--;
       for (int i = 0; i < k; i++)
       {
        if (seq[i] >= seq[i+1])
        {
            swap(&seq[i], &seq[i+1]);
            stop = 0;
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
    printf("Array not Sorted : \n");
    printArray(seq, nelem);
    bubbleSort(seq, nelem);
    printf("Sorted array (bubble sort(v1)) : \n");
    printArray(seq, nelem);
    //---------------------------
    bubbleSort2(seq, nelem);
    printf("Sorted array (bubble sort(v2)) : \n");
    printArray(seq, nelem);
    return 0;
}
