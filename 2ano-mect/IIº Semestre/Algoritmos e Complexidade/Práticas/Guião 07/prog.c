/**
 * Nome Jodionisio da Lucinda João Muachifi
 * Nº Mec: 97147
 * Cadeira de : Algoritmo e Complexidade | 2º Ano-2º semestre
 * Curso: MIECT  
 * Abril 2021
 */

#include <stdio.h>

static int NUM_MULT;

int recursiveFunction(unsigned int n)
{
    int s;
    if (n == 0 || n == 1 || n == 2)
    {
        return 1;
    }
    else
    {
        s = recursiveFunction(n - 1) + recursiveFunction(n - 2);
        for (int k = 0; k <= n - 3; k++)
        {
            NUM_MULT++;
            s += recursiveFunction(k) * recursiveFunction(n - 3 - k);
        }
    }
    return s;
}
int danamicFunction(unsigned n)
{
    int a[n + 1];
    if (n == 0 || n == 1 || n == 2)
    {
        return 1;
    }
    else
    {
        a[0] = 1;
        a[1] = 1;
        a[2] = 1;
        for (int i = 3; i <= n; i++)
        {
            a[i] = a[i - 1] + a[i - 2];

            for (int k = 0; k <= i - 3; k++)
            {
                NUM_MULT++;
                a[i] += a[k] * a[i - k - 3];
            }
        }
    }
    return a[n];
}

int main(int argc, char const *argv[])
{
    printf("-------------------------------------------------------------------\n");
    printf("\tn\t|\tF(n)-Versão Recursiva\t|\tNº Multi\n");
    printf("-------------------------------------------------------------------\n");
    for (int n = 0; n <= 25; n++)
    {
        NUM_MULT = 0;
        recursiveFunction(n);

        printf("|%10d %20d  %30d  |\n", n, recursiveFunction(n), NUM_MULT);
    }
    printf("-------------------------------------------------------------------\n");
    printf("\n");

    printf("-------------------------------------------------------------------\n");
    printf("\tn\t|\tF(n)-Versão Dinâmica\t|\tNº Multi\n");
    printf("-------------------------------------------------------------------\n");
    for (int n = 0; n <=25; n++)
    {
        NUM_MULT = 0;
        danamicFunction(n);

        printf("|%10d %20d  %30d  |\n", n, danamicFunction(n), NUM_MULT);
    }
    printf("-------------------------------------------------------------------\n");

  
    return 0;
}
