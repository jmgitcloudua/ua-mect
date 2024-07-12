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
* totalNumEl: total number os elements - result
* a : array
* n: number of elements or size
*/
int qtyElementsSeq(int a[], unsigned int n)
{
    unsigned int i;
    assert(n > 2);
    for (i = 1; i < n - 1; i++)
    {
        if (a[i] == a[i - 1] + a[i + 1])
        {
            totalNumEl++;
        }
        numComp++;
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
    unsigned int n = sizeof(a1) / sizeof(a1[0]);

    //------Testing array a1
    numComp = 0;
    totalNumEl = 0;
    qtyElementsSeq(a1, n);
    printf("[Array 1] Result = %d , NumComp = %d\n", totalNumEl, numComp);
    //------Testing array a2
    numComp = 0;
    totalNumEl = 0;
    qtyElementsSeq(a2, n);
    printf("[Array 2] Result = %d , NumComp = %d\n", totalNumEl, numComp);
    //------Testing array a3
    numComp = 0;
    totalNumEl = 0;
    qtyElementsSeq(a3, n);
    printf("[Array 3] Result = %d , NumComp = %d\n", totalNumEl, numComp);
    //------Testing array a4
    numComp = 0;
    totalNumEl = 0;
    qtyElementsSeq(a4, n);
    printf("[Array 4] Result = %d , NumComp = %d\n", totalNumEl, numComp);
    //------Testing array a5
    numComp = 0;
    totalNumEl = 0;
    qtyElementsSeq(a5, n);
    printf("[Array 5] Result = %d , NumComp = %d\n", totalNumEl, numComp);

    return 0;
}
