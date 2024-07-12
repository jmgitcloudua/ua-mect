/**
 * Nome Jodionisio da Lucinda João Muachifi
 * Nº Mec: 97147
 * Cadeira de : Algoritmo e Complexidade | 2º Ano-2º semestre
 * Curso: MIECT  
 * Abril 2021
 */
#include <stdio.h>
#include <assert.h>
#define TRUE 1
#define FALSE 0

static int NUM_OP;

/**** All variables names****
* 
* NUM_OP: number of operations
* pgElementsSeq(a[], n): will return a result
* a : array
* n: number of elements or size
*/
int pgElementsSeq(int a[], int n)
{

    assert(n > 2);

    int r = a[1] / a[0];
    NUM_OP++;
    for (int i = 2; i < n; i++)
    {
        NUMclear_OP++;
        
        if (a[i] != r * a[i - 1]) //negative logic
        {
            return FALSE;
        }
    }
    return TRUE;
}
int main(int argc, char const *argv[])
{
    unsigned int n = 10;
    int res;
    int a1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int a2[] = {1, 2, 4, 4, 5, 6, 7, 8, 9, 10};
    int a3[] = {1, 2, 4, 8, 5, 6, 7, 8, 9, 10};
    int a4[] = {1, 2, 4, 8, 16, 6, 7, 8, 9, 10};
    int a5[] = {1, 2, 4, 8, 16, 32, 7, 8, 9, 10};
    int a6[] = {1, 2, 4, 8, 16, 32, 64, 8, 9, 10};
    int a7[] = {1, 2, 4, 8, 16, 32, 64, 128, 9, 10};
    int a8[] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 10};
    int a9[] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512};

    //------Testing array a1
    NUM_OP = 0;
    res = pgElementsSeq(a1, n);
    printf("[Array 1] Result = %d , NUM_OP = %d\n", res, NUM_OP);
    //------Testing array a2
    NUM_OP = 0;
    res = pgElementsSeq(a2, n);
    printf("[Array 2] Result = %d , NUM_OP = %d\n", res, NUM_OP);
    //------Testing array a3
    NUM_OP = 0;
    res = pgElementsSeq(a3, n);
    printf("[Array 3] Result = %d , NUM_OP = %d\n", res, NUM_OP);
    //------Testing array a4
    NUM_OP = 0;
    res =pgElementsSeq(a4, n);
    printf("[Array 4] Result = %d , NUM_OP = %d\n", res, NUM_OP);
    //------Testing array a5
    NUM_OP = 0;
    res = pgElementsSeq(a5, n);
    printf("[Array 5] Result = %d , NUM_OP = %d\n", res, NUM_OP);
    //------Testing array a6
    NUM_OP = 0;
    res = pgElementsSeq(a6, n);
    printf("[Array 6] Result = %d , NUM_OP = %d\n", res, NUM_OP);
    //------Testing array a7
    NUM_OP = 0;
    res = pgElementsSeq(a7, n);
    printf("[Array 7] Result = %d , NUM_OP = %d\n", res, NUM_OP);
    //------Testing array a8
    NUM_OP = 0;
    res = pgElementsSeq(a8, n);
    printf("[Array 8] Result = %d , NUM_OP = %d\n", res, NUM_OP);
    //------Testing array a9
    NUM_OP = 0;
    res = pgElementsSeq(a9, n);
    printf("[Array 9] Result = %d , NUM_OP = %d\n", res, NUM_OP);

    return 0;
}
