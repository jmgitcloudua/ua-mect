#include <stdio.h>

//version 1.0
/*unsigned int searchMin(int seq[], unsigned int nelem, int start){
    unsigned int indexMin = start, indexCurrent;
    for (indexCurrent =  start + 1 ; indexCurrent < nelem; indexCurrent++)
    {
        if (seq[indexCurrent] < seq[indexMin])
        {
           indexMin = indexCurrent;
        }
        
    }
    return indexMin;

}*/
//version 2.0
unsigned int searchMin(int seq[], unsigned int nelem){
    unsigned int indexMin = 0, indexCurrent;
    for (indexCurrent =  1 ; indexCurrent < nelem; indexCurrent++)
    {
        if (seq[indexCurrent] < seq[indexMin])
        {
           indexMin = indexCurrent;
        }
        
    }
    return indexMin;

}
int main(int argc, char const *argv[])
{
    int seq[10] = {4, 2, 8, 100, 40, 80, 120, 220, 16, 10};
    unsigned int nelem = sizeof(seq)/sizeof(*seq);
    unsigned int min = searchMin(seq, nelem);

    printf("The min value searched is in index: %d\n", min);

    return 0;
}
