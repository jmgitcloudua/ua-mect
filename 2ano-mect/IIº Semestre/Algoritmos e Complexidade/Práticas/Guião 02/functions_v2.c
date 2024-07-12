#include <stdio.h>



static int NUM_ITR;
/**
 * Nome Jodionisio da Lucinda João Muachifi
 * Nº Mec: 97147
 * Cadeira de : Algoritmo e Complexidade | 2º Ano-2º semestre
 * Curso: MIECT  
 * Marcço 2021
 */
unsigned int f1(unsigned int n){
    unsigned int i, j, r = 0;
    for (i = 1; i <= n; i++)
    {
        for (j = 1; j <= n; j++)
        {
            r += 1;
            NUM_ITR++;
        }
        
    }
    return r;
}
unsigned int f2(unsigned int n){
    unsigned int i, j, r = 0;
    for (i = 1; i <= n; i++)
    {
        for (j = 1; j <= i; j++)
        {
            r += 1;
            NUM_ITR++;
        }
        
    }
    return r;
}
unsigned int f3(unsigned int n){
    unsigned int i, j, r = 0;
    for (i = 1; i <= n; i++)
    {
        for (j = i; j <= n; j++)
        {
            r += j;
            NUM_ITR++;
        }
        
    }
    return r;
}
unsigned int f4(unsigned int n){
    unsigned int i, j, r = 0;
    for (i = 1; i <= n; i++)
    {
        for (j = i; j >= 1; j /=10)
        {
            r += i;
            NUM_ITR++;
        }
        
    }
    return r;
}
int main(void){
    unsigned int r;
    printf("n\tf1(n)\tI(f1)\tf2(n)\tI(f2)\tf3(n)\tI(f3)\tf4(n)\tI(f4)\n");
	for(unsigned int n = 1; n <= 15; n++) {
       printf("%4d\t",n);

        NUM_ITR = 0;
         r = f1(n);
        printf("%7u\t%7u\t",r, NUM_ITR);

        NUM_ITR = 0;
        r = f2(n);
        printf("%7u\t%7u\t",r, NUM_ITR);

       NUM_ITR = 0;
       r = f3(n);
       printf("%7u\t%7u\t",r, NUM_ITR);

       NUM_ITR = 0;
       r = f4(n);
      printf("%7u\t%7u\n",r, NUM_ITR);
      
        
	}
   
    return 0;
}
