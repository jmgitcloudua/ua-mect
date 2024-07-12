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
      int i, j, r = 0;
      int itr = 0; //nº de iterações
      for (i = 1; i <= n; i++){
            for (j = 1; j <= n; j++){
                        r += 1;
                        itr++;
                      
            }
      }
      printf("Resultado r = %d\n", r);
      printf("Somas = %d\n", itr);
      return r;


}
