/**
 * Nome Jodionisio da Lucinda João Muachifi
 * Nº Mec: 97147
 * Cadeira de : Algoritmo e Complexidade | 2º Ano-2º semestre
 * Curso: MIECT  
 * Abril 2021
 */

#include <stdio.h>
#include <assert.h>

int combination(int n, int k)
{ //comb n element k to k

    assert(k >= 0 && n >= k);

    int result = 1;

    if (k > 0 && k < n)
    {
        result = combination(n - 1, k - 1) + combination(n - 1, k); // two recursive call
    }

    return result;
}

int main(int argc, char const *argv[])
{
    unsigned int n, k;

    do
    {

        printf("Type the two values: \n");
        scanf("%d %d", &n, &k);
        int comb = combination(n, k);
        printf("Comb(%d,%d) = %d\n", n, k, comb);
    } while (n <= k);

    return 0;
}
