/**
 * Nome Jodionisio da Lucinda João Muachifi
 * Nº Mec: 97147
 * Cadeira de : Algoritmo e Complexidade | 2º Ano-2º semestre
 * Curso: MIECT  
 * Abril 2021
 */
#include <stdio.h>
#include <assert.h>

static int numComp;
static int totalNumEl;

/**** All variables names****
* 
* numComp: number of compararisons
* totalNumEl: total number os elements-result
* a : array
* n: number of elements or size
*/
int qtyTripletsSeq(int a[], unsigned int n)
{
    unsigned int i, k, j;

    assert(n > 2);

    for (i = 0; i <= n - 1; i++)
    {
        for (j = i + 1; j <= n - 1; j++)
        {
            for (k = j + 1; k < n; k++)
            {
                numComp++;
                if (a[k] == a[i] + a[j])
                {
                    totalNumEl++;
                }
            }
        }
    }
    return totalNumEl;
}

int main(int argc, char const *argv[])
{
    int a1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int a2[] = {1, 2, 1, 4, 5, 6, 7, 8, 9, 10};
    int a3[] = {1, 2, 1, 3, 2, 6, 7, 8, 9, 10};
    int a4[] = {0, 2, 2, 0, 3, 3, 0, 4, 4, 0};
    int a5[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int a6[] = {58, 86, 33, 69, 40, 2, 28, 19, 30, 0};
    int a7[] = {96, 70, 14, 42, 95};
    int a8[] = {41, 81, 26, 11, 10, 49, 75, 29, 11, 43, 22, 20, 44, 39, 34, 89, 33, 32, 78, 98};
    int a9[] = {19, 48, 10, 89, 62, 31, 71, 44, 13, 48, 73, 88, 35, 96, 30, 74, 29, 12, 67, 51, 99, 54, 95, 5, 97, 16, 36, 82, 69, 83};
    int a10[] = {3, 64, 77, 41, 95, 25, 14, 94, 18, 59, 54, 13, 90, 11, 98, 58, 7, 52, 96, 60, 4, 50, 87, 25, 31, 97, 58, 47, 75, 94, 9, 14, 88, 60, 7, 41, 8, 85, 82, 52};
    unsigned int n = sizeof(a1) / sizeof(a1[0]);

    //------Testing array a1
    numComp = 0;
    totalNumEl = 0;
    qtyTripletsSeq(a1, n);
    printf("[Array 1] Result = %d , NumComp = %d\n", totalNumEl, numComp);
    //------Testing array a2
    numComp = 0;
    totalNumEl = 0;
    qtyTripletsSeq(a2, n);
    printf("[Array 2] Result = %d , NumComp = %d\n", totalNumEl, numComp);
    //------Testing array a3
    numComp = 0;
    totalNumEl = 0;
    qtyTripletsSeq(a3, n);
    printf("[Array 3] Result = %d , NumComp = %d\n", totalNumEl, numComp);
    //------Testing array a4
    numComp = 0;
    totalNumEl = 0;
    qtyTripletsSeq(a4, n);
    printf("[Array 4] Result = %d , NumComp = %d\n", totalNumEl, numComp);
    //------Testing array a5
    numComp = 0;
    totalNumEl = 0;
    qtyTripletsSeq(a5, n);
    printf("[Array 5] Result = %d , NumComp = %d\n", totalNumEl, numComp);
     //------Testing array a6
    numComp = 0;
    totalNumEl = 0;
    qtyTripletsSeq(a7, sizeof(a6) / sizeof(a6[0]));
    printf("[Array 6] Result = %d , NumComp = %d\n", totalNumEl, numComp);

    printf("--------------------------------------\n");

     //------Testing array a7
    numComp = 0;
    totalNumEl = 0;
    qtyTripletsSeq(a7, sizeof(a7) / sizeof(a7[0]));
    printf("[Array 7] Result = %d , NumComp = %d\n", totalNumEl, numComp);

     //------Testing array a8
    numComp = 0;
    totalNumEl = 0;
    qtyTripletsSeq(a8, sizeof(a8) / sizeof(a8[0]));
    printf("[Array 8] Result = %d , NumComp = %d\n", totalNumEl, numComp);
     //------Testing array a9
    numComp = 0;
    totalNumEl = 0;
    qtyTripletsSeq(a9, sizeof(a9) / sizeof(a9[0]));
    printf("[Array 9] Result = %d , NumComp = %d\n", totalNumEl, numComp);
     //------Testing array a10
    numComp = 0;
    totalNumEl = 0;
    qtyTripletsSeq(a10, sizeof(a10) / sizeof(a10[0]));
    printf("[Array 10] Result = %d , NumComp = %d\n", totalNumEl, numComp);

    
    return 0;
}
