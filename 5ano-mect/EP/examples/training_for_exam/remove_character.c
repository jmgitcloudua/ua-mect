#include <stdio.h>

//Remove Characters in String Except Alphabets
void removeCharacter(char *str, int i)
{
    if (str[i] == '\0')
        return;
    if (!((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z')))
    {
        int j = i;
        while (str[j] != '\0')
        {
            str[j] = str[j + 1];
            j++;
        }
        removeCharacter(str, i);
    }
    else
        removeCharacter(str, i + 1);
}

int main()
{
    char str[1000];
    printf("Enter a string: ");
    if (scanf("%[^\n]%*c", str) != 1)
    {
        printf("Invalid input");
        return 1;
    }
    removeCharacter(str, 0);
    printf("String after removing characters except alphabets: %s\n", str);
    return 0;
}