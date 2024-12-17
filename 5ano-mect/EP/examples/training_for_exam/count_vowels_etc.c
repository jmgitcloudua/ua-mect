#include <stdio.h>
#include <string.h>

int count_vowels_etc(char *str, int *vowels, int *consonants, int *digits, int *spaces, int *symbols);

int main()
{
    char str[1000];
    int vowels = 0, consonants = 0, digits = 0, spaces = 0, symbols = 0;
    printf("Enter a string: ");
    if (scanf("%[^\n]%*c", str) != 1)
    {
        printf("Invalid input");
        return 1;
    }
    count_vowels_etc(str, &vowels, &consonants, &digits, &spaces, &symbols);
    printf("Vowels: %d\n", vowels);
    printf("Consonants: %d\n", consonants);
    printf("Digits: %d\n", digits);
    printf("White spaces: %d\n", spaces);
    printf("Symbols: %d\n", symbols);
    return 0;
}

int count_vowels_etc(char *str, int *vowels, int *consonants, int *digits, int *spaces, int *symbols)
{
    static int i = 0;
    if (!str[i])
        return 0;
    else
    {
        if (str[i] == 'a' || str[i] == 'e' || str[i] == 'i' ||
            str[i] == 'o' || str[i] == 'u' || str[i] == 'A' ||
            str[i] == 'E' || str[i] == 'I' || str[i] == 'O' ||
            str[i] == 'U')
            (*vowels)++;
        else if ((str[i] >= 'a' && str[i] <= 'z') ||
                 (str[i] >= 'A' && str[i] <= 'Z'))
            (*consonants)++;
        else if (str[i] >= '0' && str[i] <= '9')
            (*digits)++;
        else if (str[i] == ' ')
            (*spaces)++;
        else
            (*symbols)++;
        i++;
        count_vowels_etc(str, vowels, consonants, digits, spaces, symbols);
    }
    return 0;
}