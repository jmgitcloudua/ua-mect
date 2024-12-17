#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 17/10/2023
// allocate memory for a string

int main()
{
    char *s = "Exemplo de uma string";
    // char w[] = "Exemplo de uma string";

    // w[5] = 'x';
    // printf("%s\n", s);
    // s = "Another string";
    // w[21] = 'x';
    // w[10001] = '\0';
    // printf("%s\n", s);
    // printf("%s\n", w);
    // printf("%c\n", w[5]);

    printf("-------------\n");

    // char * p = malloc(100 );
    char *q = malloc(strlen(s) + 1);
    for (int i = 0; i < strlen(s); i++)
    {
        q[i] = s[i];
    }
    q[strlen(s)] = '\0'; // p[12] = '\0' = p[12] = 0
    q[5] = 'Y';
    //free(q); // liberta a memoria alocada
    printf("%s\n", q);

    return 0;
}