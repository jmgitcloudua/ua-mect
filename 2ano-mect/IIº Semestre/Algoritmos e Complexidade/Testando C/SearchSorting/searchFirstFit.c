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
    int seq[10] = {2, 4, 5, 6,  7, 8, 10, 12, 20, 30};
    unsigned int nelem = sizeof(seq)/sizeof(*seq);
    printf("Choice one value you want to search\n");
    printArray(seq, nelem);
    unsigned int n;
    printf("Value : ");
    scanf("%d",&n);
    unsigned int firstFit = searchFirstFit(seq, nelem, 0, n);
    printf("The First Fit value searched is in index: %d\n", firstFit);
    return 0;
}
