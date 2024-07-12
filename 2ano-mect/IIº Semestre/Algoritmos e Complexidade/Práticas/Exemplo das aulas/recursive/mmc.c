/**
 * Nome Jodionisio da Lucinda João Muachifi
 * Nº Mec: 97147
 * Cadeira de : Algoritmo e Complexidade | 2º Ano-2º semestre
 * Curso: MIECT  
 * Abril 2021
 */

#include <stdio.h>
#include <assert.h>

int mdc(int n1, int n2)
{

    if (n2 != 0)
    {
        return mdc(n2, n1 % n2);
    }
    else
    {
        return n1;
    }
}
int mmc(int n1, int n2)
{
    return (n1 / mdc(n1, n2)) * n2;
}
int main(int argc, char const *argv[])
{
    unsigned int n1, n2;
    while (n1 > 0 && n2 > 0)
    {
        printf("Digite dois valores:\n  ");
        scanf("%d %d", &n1, &n2);
        int m = mmc(n1, n2);
        printf("MMC(%d, %d) = %d\n", n1, n2, m);
    }

    return 0;
}
