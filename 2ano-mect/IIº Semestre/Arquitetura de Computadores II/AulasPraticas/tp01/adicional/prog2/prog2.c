#include <detpic32.h>
#define STR_MAX_SIZE 20

char *strcat(char *, char *);
char *strcpy(char *, char *);
int strlen(char *);
int main(void)
{
    static char str1[STR_MAX_SIZE + 1];
    static char str2[STR_MAX_SIZE + 1];
    static char str3[2 * STR_MAX_SIZE + 1];
    printStr("Introduza 2 strings: ");
    readStr(str1, STR_MAX_SIZE);
    readStr(str2, STR_MAX_SIZE);
    printStr("Resultados:\n");
    prinInt(strlen(str1), 10);
    prinInt(strlen(str2), 10);
    strcpy(str3, str1);
    printStr(strcat(str3, str2));
    printInt10(strcmp(str1, str2));
    return 0;
}

int strlen(char *s)
{
    int len;
    for (len = 0; *s != '\0'; len++, s++)
        ;
    return len;
}

char *strcpy(char *dst, char *src)
{
    char *p = dst;
    for (; (*dst = *src) != '\0'; dst++, src++)
        ;
    return p;
}

char *strcat(char *dst, char *src)
{
    char *p = dst;

    for (; *dst != '\0'; dst++)
        ;
    strcpy(dst, src);
    return p;
}

// Returned value is:
// < 0 string "s1" is "less than" string "s2"
// = 0 string "s1" is equal to string "s2"
// > 0 string "s1" is "greater than" string "s2"

int strcmp(char *s1, char *s2)
{
    for (; (*s1 == *s2) && (*s1 != '\0'); s1++, s2++)
        ;
    return (*s1 - *s2);
}