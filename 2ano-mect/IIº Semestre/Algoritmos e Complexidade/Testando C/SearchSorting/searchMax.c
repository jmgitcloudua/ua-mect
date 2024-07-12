#include <stdio.h>

//version 1.0
/*unsigned int searchMax(int seq[], unsigned int nelem, int start){
    unsigned int indexMax = start, indexCurrent;
    for (indexCurrent =  start + 1 ; indexCurrent < nelem; indexCurrent++)
    {
        if (seq[indexCurrent] > seq[indexMax])
        {
           indexMax = indexCurrent;
        }
        
    }
    return indexMax;

}*/
//version 2.0
unsigned int searchMax(int seq[], unsigned int nelem){
    unsigned int indexMax = 0, indexCurrent;
    for (indexCurrent =  1 ; indexCurrent < nelem; indexCurrent++)
    {
        if (seq[indexCurrent] > seq[indexMax])
        {
           indexMax = indexCurrent;
        }
        
    }
    return indexMax;

}
int main(int argc, char const *argv[])
{
    int seq[10] = {4, 2, 8, 100, 40, 80, 120, 220, 16, 10};
    unsigned int nelem = sizeof(seq)/sizeof(*seq);
    unsigned int max = searchMax(seq, nelem);

    printf("The max value searched is in index: %d\n", max);

    return 0;
}
