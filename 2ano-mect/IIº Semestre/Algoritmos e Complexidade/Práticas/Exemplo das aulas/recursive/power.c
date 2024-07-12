/**
 * Nome Jodionisio da Lucinda João Muachifi
 * Nº Mec: 97147
 * Cadeira de : Algoritmo e Complexidade | 2º Ano-2º semestre
 * Curso: MIECT  
 * Abril 2021
 */

#include <stdio.h>
#include <assert.h>

double power(double value, unsigned int n)
{
    if (n > 0)
    {
        return value * power(value, n - 1);
    }
    return 1;
}

int main(int argc, char const *argv[])
{
    unsigned int n;
    double value;

    do
    {

        printf("Type the two values: \n");
        scanf("%lf %d", &value, &n);
        double p = power(value, n);
        printf("Power(%.2lf, %d) = %.2lf\n", value, n, p);
    } while (n > 0);
    return 0;
}
