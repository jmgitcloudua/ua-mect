/**
 * Nome Jodionisio da Lucinda João Muachifi
 * Nº Mec: 97147
 * Cadeira de : Algoritmo e Complexidade | 2º Ano-2º semestre
 * Curso: MIECT  
 * Abril 2021
 */

#include <stdio.h>


static int NUM_REC_CALL;

int T1(unsigned int n)
{
    NUM_REC_CALL++;
    if (n == 0)
    {
        return 0;
    }
    if (n > 0)
    {
        return T1(n / 4) + n;
    }
}
int T2(unsigned int n)
{
    NUM_REC_CALL++;
    if (n <= 3)
    {
        return n;
    }
    if (n > 3)
    {
        return T2(n / 4) + T2((n + 3) / 4)+n;
    }
}
int T3(unsigned int n)
{
    NUM_REC_CALL++;
    if (n <= 3)
    {
        return n;
    }
    else if (n % 4 == 0)
    {
        return 2 * T3(n / 4) + n;
    }
    else
    {
        return T3(n / 4) + T3((n + 3) / 4) + n;
    }
}
int main(int argc, char const *argv[])
{
    printf("-------------------------------------------------\n");
    printf("|\tn\t|\tT1(n)\t|\tNCR1\t|\n");
    printf("-------------------------------------------------\n");

    for (int n = 0; n <= 28; n++)
    {

        NUM_REC_CALL = 0;
        T1(n);
       

        printf("|\t%d\t|\t%d\t|\t%d\t|\n", n, T1(n), NUM_REC_CALL);
    }
    printf("-------------------------------------------------\n");
    printf("\n");
    //----------------------------------------------------------
    printf("-------------------------------------------------\n");
    printf("|\tn\t|\tT2(n)\t|\tNCR2\t|\n");
    printf("-------------------------------------------------\n");

    for (int n = 0; n <= 28; n++)
    {

        NUM_REC_CALL = 0;
        T2(n);
       

        printf("|\t%d\t|\t%d\t|\t%d\t|\n", n, T2(n), NUM_REC_CALL);
    }
    printf("-------------------------------------------------\n");
    printf("\n");
    //-------------------------------------------------------------
    printf("-------------------------------------------------\n");
    printf("|\tn\t|\tT3(n)\t|\tNCR3\t|\n");
    printf("-------------------------------------------------\n");

    for (int n = 0; n <= 28; n ++)
    {

        NUM_REC_CALL = 0;
        T3(n);
       

        printf("|\t%d\t|\t%d\t|\t%d\t|\n", n, T3(n), NUM_REC_CALL);
    }
    printf("-------------------------------------------------\n");
    return 0;
}

