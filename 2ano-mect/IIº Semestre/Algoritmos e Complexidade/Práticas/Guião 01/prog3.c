#include <stdio.h>
#include <math.h>

int main(void){
      double squarex, line, sqrtx, value, i, j;
      //printf("What is the value  ? ");
       //scanf("%lf",&value);
      printf("How many line? ");
      scanf("%lf",&line);
      //printf("%-11s %-11s %-11s \n","VALUE I","SQUARE","SQRT");
      //printf("%-11s %-11s %-11s \n","--------","--------","-------");
      printf("-------------------------------------------------\n");
	printf("|\ti\t|\tQ\t|\tR\t|\n");
	printf("-------------------------------------------------\n");
      for(i = 1; i<=line; i++){
            for ( j = 1; j <= line; j++);
            {
                  squarex = i*i;
                  sqrtx = sqrt(i);
                  printf("|\t%3.0f\t|\t%1.2f\t|\t%1.2f\t|\n ",i,squarex,sqrtx);
            }
      }
      printf("------------------------------------------------\n");
      return 0;

}