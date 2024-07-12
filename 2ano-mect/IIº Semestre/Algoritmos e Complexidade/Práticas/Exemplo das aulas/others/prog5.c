#include <stdio.h>
#include <assert.h>

static int NUM_MULT;

void matrix(unsigned int n)
{

   
    int a[3][3];
    int b[3][3];
    int c[3][3];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            c[i][j] = 0;
            for (int k = 0; k < n; k++)
            {
                NUM_MULT++;
                c[i][j] +=a[i][k]*b[k][j];
            }
        }
    }
}

int main(int argc, char const *argv[])
{
    for (int n = 1; n <= 3; n++)
    {
        NUM_MULT = 0;
        matrix(n);
    
    }
    printf("NUM_MUlT = %5d \n", NUM_MULT);
    
    return 0;
}
