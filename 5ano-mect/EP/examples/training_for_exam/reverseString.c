#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void revStr(char *str);
char *revStr2(const char *str);
int main()
{
    char str[100];
    printf("Enter a string: ");
    if (scanf("%s", str) != 1)
    {
        printf("Error reading string\n");
        exit(1);
    }
    revStr(str);
    printf("Reversed string: %s\n", str);
    printf("Enter a string: ");
    if (scanf("%s", str) != 1)
    {
        printf("Error reading string\n");
        exit(1);
    }
    char *rev = revStr2(str);
    printf("Reversed string: %s\n", rev);

    free(rev);

    return 0;
}
// reverse string
void revStr(char *str)
{

    int length = strlen(str);
    for (int i = 0; i < length / 2; i++)
    {
        char temp = str[i];
        str[i] = str[length - i - 1];
        str[length - i - 1] = temp;
    }
}
// Other solution
char *revStr2(const char *str)
{
    int length = strlen(str);
    char *rev = (char *)malloc(sizeof(char) * (length + 1));
    if (rev == NULL)
    {
        printf("Error allocating memory\n");
        exit(1);
    }

    strcpy(rev, str);

    for (int i = 0; i < length / 2; i++)
    {
        char temp = str[i];
        rev[i] = str[length - i - 1];
        rev[length - i - 1] = temp;
    }

    return rev;
}