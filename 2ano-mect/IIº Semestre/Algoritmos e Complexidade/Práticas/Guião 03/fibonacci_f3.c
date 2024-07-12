/**
 * Nome Jodionisio da Lucinda João Muachifi
 * Nº Mec: 97147
 * Cadeira de : Algoritmo e Complexidade | 2º Ano-2º semestre
 * Curso: MIECT  
 * Abril 2021
 */
#include <stdio.h>
#include <math.h>
#include "elapsed_time.h"

typedef unsigned long long int u64;

//defining consat value for third way fibonacci calculation
long double c1 = 0.24253562503633297352l; // = 1/sqrt(5)
long double c2 = 1.27019663313689157536l; // = ln(GOLDEN_NUM) or ln((1 + sqrtl(5)) / 2)
static int numOps ;

/*Third Way - Fibonacci*/
u64 fibonacci3(int n){
    numOps+=10;
    return roundl(c1 * expl(n * c2));
     
}
int main(void)
{
    printf("NUM_OPS\t| \tFIBONACCI_NUM\t | ELAPSED_TIME(µs)\n");
	printf("---------------------------------------------------\n");

    (void)elapsed_time();
	for(int i = 0; i < 100; i++) {
        numOps = 0;
		u64 fibo =  fibonacci3(i);
		double exeTime = elapsed_time()*1000000;
		printf("%2d  -> %18llu\t | %10f\n", numOps,fibo,exeTime);
	}
    return 0;
}
