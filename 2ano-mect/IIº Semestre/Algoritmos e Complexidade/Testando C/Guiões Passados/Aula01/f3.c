#include <stdio.h>

int main(){
     int n;
     printf("Digite o valor de n positivo : ") ;
     scanf("%d",&n);
      int i, j, r = 0;
      int sums = 0;
      for (i = 1; i <= n; i++){
            for (j = i; j <= n; j++){
                        r += j;
                        sums++;
            }
      }
      printf("Resultado r = %d\n", r);
      printf("Somas = %d\n", sums);
      return r;
}
