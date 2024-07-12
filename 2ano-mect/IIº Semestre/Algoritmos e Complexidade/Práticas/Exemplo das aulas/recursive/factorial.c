/**
 * Nome Jodionisio da Lucinda João Muachifi
 * Nº Mec: 97147
 * Cadeira de : Algoritmo e Complexidade | 2º Ano-2º semestre
 * Curso: MIECT  
 * Abril 2021
 */
#include <stdio.h>
#include <assert.h>

int factorial(int n)
{
    assert(n >= 0);

    if (n == 0)
    {
        return 1;
    }
    else
    {
        return n * factorial(n - 1);
    }
}
int main(int argc, char const *argv[])
{
    unsigned int n;
    while (n >= 0)
    {
        printf("Digite um valor:  ");
        scanf("%d", &n);
        int f = factorial(n);
        printf("%d! = %d\n", n, f);
    }

    return 0;
}
