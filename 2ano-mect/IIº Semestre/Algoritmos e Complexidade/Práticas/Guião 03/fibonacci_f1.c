/**
 * Nome Jodionisio da Lucinda João Muachifi
 * Nº Mec: 97147
 * Cadeira de : Algoritmo e Complexidade | 2º Ano-2º semestre
 * Curso: MIECT  
 * Abril 2021
 */
#include <stdio.h>
#include "elapsed_time.h"

typedef unsigned long long int u64;

u64 numOps = 0;

u64 fibonacci_f1(int n)
{
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;
    numOps += 1;
    return fibonacci_f1(n - 1) + fibonacci_f1(n - 2);
}
int main(void)
{
    printf("\tFIBONACCI_NUM\t | \tOPS_NUM\t   | ELAPSED_TIME(ms)\n");
    printf("-------------------------------------------------------------\n");

    (void)elapsed_time();
    for (int i = 0; i < 100; i++)
    {
        numOps = 0;
        u64 fibo = fibonacci_f1(i);
        double exeTime = elapsed_time()*1000;

        printf("%18llu\t | %10llu\t  | %10f\n", fibo, numOps, exeTime);
    }

    return 0;
}