#include <stdio.h>

int main(int argc,char **argv){
      for(int i = 0;i < argc;i++) // definition of a variable anywhere (a la C++) is a c99 feature
      printf("%s\n",argv[i]); // compile this using "cc -Wall -O2 -std=c99 main.c"
return 0;
}