#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>


int main(int argc, char const *argv[])
{
    printf("0"); fflush(stdout);
    for (int i = 0; i < 2; i++)
    {
        if (fork() == 0)
        {
            
            sleep(1);
            printf("%d", 2*i+1);fflush(stdout);
            sleep(1);
             printf("%d", 2*i+2);fflush(stdout);
             exit(0);
        }
        
    }
    for (int i = 0; i < 2; i++)
    {
        wait(NULL);
    }
    
    
    return 0;
}
