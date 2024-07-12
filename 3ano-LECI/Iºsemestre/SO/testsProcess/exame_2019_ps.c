#include <stdio.h>
#include <unistd.h>

int main(int argc, char argv[]){
    printf("A\n");
    if(fork() != 0){
        fork();
         printf("B\n");
          printf("C\n");
    }else{
         printf("D\n");
         execlp("echo", "echo", "sop", NULL);
         printf("E\n");

    }
}