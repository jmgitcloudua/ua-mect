#include <stdio.h>

// First fit - Primeiro valor que serve
int searchFirstFit(int seq[], unsigned int nelem, unsigned int start, int value){
    unsigned int indexCurrent;
    for (indexCurrent = start; indexCurrent < nelem; indexCurrent++)
    {
        if (seq[indexCurrent] <= value)
        {
            return indexCurrent;
        }
        return -1; // if the value not found
    }
    
}
// Worst fit - Pior valor que serve
int searchWorstFit(int seq[], unsigned int nelem, unsigned int start, int value){
    int indexWorst;
    unsigned int indexCurrent;
    indexWorst = searchFirstFit(seq, nelem, start, value);
    if (indexWorst == -1)
    {
        return -1;
    }
    for (indexCurrent = indexWorst + 1; indexCurrent < nelem; indexCurrent++)
    {
       if (seq[indexCurrent] < seq[indexWorst] )
       {
           indexWorst = indexCurrent;
       }
       
    }
    
    return indexWorst;
}
void printArray(int seq[], int size){
    int i = 0;
    for ( i = 0; i < size; i++)
    {
        printf("%d\t", seq[i]);
    }
    printf("\n");
}
int main(int argc, char const *argv[])
{
    int seq[10] = {4, 2, 8, 100, 40, 80, 120, 220, 16, 10};
    unsigned int nelem = sizeof(seq)/sizeof(*seq);
    printf("Choice one value you want to search\n");
    printArray(seq, nelem);
    unsigned int n;
    printf("Value : ");
    scanf("%d",&n);
    unsigned int worstFit = searchWorstFit(seq, nelem, 0, n);
    printf("The Worst Fit value searched is in index: %d\n", worstFit);
    return 0;
}
