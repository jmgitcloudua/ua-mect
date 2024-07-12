#include <stdio.h>

int main(void){
    
    // sizeof evaluates the size of a variable
     printf("Size of void: %zu byte\n", sizeof(void));
     printf("Size of char: %zu byte\n", sizeof(char));
     printf("Size of short: %zu byte\n", sizeof(short));
     printf("Size of *void: %zu byte\n", sizeof(void *));
     printf("Size of int: %zu bytes\n", sizeof(int));
     printf("Size of float: %zu bytes\n", sizeof(float));
     printf("Size of long: %zu byte\n", sizeof(long));
     printf("Size of long long: %zu byte\n", sizeof(long long));
     printf("Size of double: %zu bytes\n", sizeof(double));
   
   
    
    


      return 0;
}