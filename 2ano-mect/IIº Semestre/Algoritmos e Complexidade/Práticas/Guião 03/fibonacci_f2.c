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

int main()
{
    printf(" \tFIBONACCI_NUM\t | \tOPS_NUM\t   | ELAPSED_TIME(µs)\n");
    printf("--------------------------------------------------------------\n");

    u64 most_recent_fibs[2] = {(u64)0, (u64)1};
   /* printf("0\t- %18llu\n", most_recent_fibs[0]);
    printf("1\t- %18llu\n", most_recent_fibs[1]);*/

    (void)elapsed_time();
    for (int i = 2; i < 94; i++)
    { // fib(94) > 2^64 -1
        u64 fibo = most_recent_fibs[0] + most_recent_fibs[1];
        numOps += 1;

        most_recent_fibs[0] = most_recent_fibs[1];
        most_recent_fibs[1] = fibo;
        double exeTime = elapsed_time()*1000000;

        printf("%18llu\t |  %10llu\t | %10f\t\n", fibo, numOps, exeTime);
    }
}