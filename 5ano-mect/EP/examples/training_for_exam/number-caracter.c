#include <stdio.h>

// Program that displays the number of characters of a string without using strlen
// Recall that the string is given on command line as an argument to the program

unsigned int str_len(char *str);

int main(int argc, char *argv[]) {
  
    if(argc != 2) {
        printf("Usage: %s <string>\n", argv[0]);
        return 1;
    }
    printf("%d\n", str_len(argv[1]));
    return 0;
}

unsigned int str_len(char *str) {
   
   if(str == NULL) return 0;
   unsigned int nc = 0;
   for(int i = 0; str[i] != '\0'; i++) {
      nc++;
   }
   return nc;
}