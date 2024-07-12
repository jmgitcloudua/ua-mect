#include <stdio.h>

/**
 * Nome Jodionisio da Lucinda João Muachifi
 * Nº Mec: 97147
 * Cadeira de : Algoritmo e Complexidade | 2º Ano-2º semestre
 * Curso: MIECT  
 * Marcço 2021
 */
int main(void){
      int n;
     printf("Digite o valor de n positivo : ") ;
     scanf("%d",&n);
       unsigned int i, j, r = 0;
       unsigned int itr = 0;
    for (i = 1; i <= n; i++)
    {
        for (j = i; j <= n; j++)
        {
            r += j;
            itr++;
        }
        
    }

      printf("Resultado r = %d\n", r);
      printf("Somas = %d\n", itr);
      return r;


}