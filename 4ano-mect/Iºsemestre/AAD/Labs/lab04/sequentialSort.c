#include <stdio.h>

int main(){
    int values[] = {1, 2, 3, 4, 5 , 6, 7 , 8 , 9 , 10};
    int nelem = 10;
    int i, j;
    int tmp;
    for ( i = 0; i < nelem-1; i++)
    {
        for ( j = i + 1; j < nelem; j++)
        {
            if (values[i] < values[j])
            {
                tmp = values[i];
                values[i] = values[j];
                values[j] = tmp;
            }
            
        }
        
    }
    printf("%d",tmp);
    
    return 0;
}


/*
Program architeture in assembly

r1 -> addr(nelem), val(nelem)
r2 -> addr(values[i])
r4 -> val[i]
r5 -> val(values[i])
r5 -> val[j]
r6 -> addr(values[i])
r7 -> val(values[j])
r8 -> nelem - 1
r8 -> tmp, (val(values[i]<values[j])), (i<nelem-1), (j<nelem)

*/