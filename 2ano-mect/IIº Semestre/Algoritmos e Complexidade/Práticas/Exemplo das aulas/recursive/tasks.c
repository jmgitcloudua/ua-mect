/**
 * Nome Jodionisio da Lucinda João Muachifi
 * Nº Mec: 97147
 * Cadeira de : Algoritmo e Complexidade | 2º Ano-2º semestre
 * Curso: MIECT  
 * Abril 2021
 */

#include <stdio.h>

unsigned int r1(unsigned int n)
{
    if (n == 0)
    {
        return 0;
    }
    return 1 + r1(n - 1);
}
unsigned int r2(unsigned int n)
{
    if (n == 0)
    {
        return 0;
    }
    if (n == 1)
    {
        return 1;
    }
    return n + r2(n - 2);
}
unsigned int r3(unsigned int n)
{
    if (n == 0)
    {
        return 0;
    }
    return 1 + 2 * r3(n - 1);
}
unsigned int r4(unsigned int n)
{
    if (n == 0)
    {
        return 0;
    }
    return 1 + r4(n - 1) + r4(n - 1);
}

int main(int argc, char const *argv[])
{
    int n;
    printf("Value n = ");
    scanf("%d", &n);

    printf("r1 -> Result = %d\n", r1(n));
    printf("r2 -> Result = %d\n", r2(n));
     printf("r3 -> Result = %d\n", r3(n));
      printf("r4 -> Result = %d\n", r4(n));

    return 0;
}
