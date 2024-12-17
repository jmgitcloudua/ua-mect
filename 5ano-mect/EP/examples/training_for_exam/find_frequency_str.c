#include <stdio.h>

int find_frequency(char *str, char toFind);

int main()
{
    char str[1000], toFind;
    printf("Enter a string: ");
    if (scanf("%[^\n]%*c", str) != 1)
    {
        printf("Invalid input");
        return 1;
    }
    printf("Enter a character to find its frequency: ");
    if (scanf("%c", &toFind) != 1)
    {
        printf("Invalid input");
        return 1;
    }
    printf("Frequency of %c = %d\n", toFind, find_frequency(str, toFind));
    return 0;
}

int find_frequency(char *str, char toFind)
{
    static int i = 0, frequency = 0;
    if (!str[i])
        return frequency;
    else
    {
        if (str[i] == toFind)
            frequency++;
        i++;
        find_frequency(str, toFind);
    }
    return frequency;
}