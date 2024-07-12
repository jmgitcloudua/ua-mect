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
    printf("-------------------------------------------------------------------------------------------------------------------------------------------------\n");
	printf("|\tn\t|\tf1(n)\t|\tI1\t|\tf2(n)\t|\tI2\t|\tf3(n)\t|\tI3\t|\tf4(n)\t|\tI4\t|\n");
    printf("-------------------------------------------------------------------------------------------------------------------------------------------------\n");

	for(int n = 1; n <= 15; n++) {
       
        NUM_ITR = 0;
         f1(n);
        NUM_ITR = 0;
        f2(n);
       NUM_ITR = 0;
        f3(n);
       NUM_ITR = 0;
        f4(n);
      
	    printf("|\t%d\t|\t%d\t|\t%d\t|\t%d\t|\t%d\t|\t%d\t|\t%d\t|\t%d\t|\t%d\t|\n", n, f1(n), NUM_ITR, f2(n), NUM_ITR, f3(n), NUM_ITR, f4(n), NUM_ITR);
       /* printf("%d\n",NUM_ITR_F2);
        printf("%d\n",NUM_ITR_F1);
        printf("%d\n",NUM_ITR_F3);*/
        
	}
    //printf("%d",NUM_ITR_F3);
    printf("-------------------------------------------------------------------------------------------------------------------------------------------------\n");

    return 0;
}
