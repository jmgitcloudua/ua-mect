#include <stdio.h>


int searchValue(int seq[], unsigned int nelem, int start, int value){
    unsigned int indexCurrent;
    for (indexCurrent =  start ; indexCurrent < nelem; indexCurrent++)
    {
        if (seq[indexCurrent]  == value)
        {
           return indexCurrent;
        }
        
    }
    return -1; // if the value is not found

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
    printf("Value : ");
    unsigned int n;
    scanf("%d",&n);
    unsigned int min = searchValue(seq, nelem, 0, n);
    printf("The searched is in index: %d\n", min);

    return 0;
}
