#include <stdio.h>
#include <stdlib.h>

char *DupString(const char *str);

int main()
{
    const char *original = "Hello, World!";
    char *copy = DupString(original);

    if (copy != NULL)
    {
        printf("Original: %s\n", original);
        printf("Copy: %s\n", copy);

        // Remember to free the allocated memory when done
        free(copy);
    }
    else
    {
        printf("Failed to duplicate the string.\n");
    }

    return 0;
}

char *DupString(const char *str)
{
    if (str == NULL)
    {
        return NULL; // Handle NULL input string
    }

    // Find the length of the input string
    int length = 0;
    while (str[length] != '\0')
    {
        length++;
    }

    // Allocate memory for the new string (including space for the null terminator)
    char *duplicate = (char *)malloc((length + 1) * sizeof(char));

    if (duplicate == NULL)
    {
        return NULL; // Memory allocation failed
    }

    // Copy each character from the original string to the new string
    for (int i = 0; i < length; i++)
    {
        duplicate[i] = str[i];
    }

    // Add null terminator to the new string
    duplicate[length] = '\0';

    return duplicate;
}