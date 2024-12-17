#include <stdio.h>
#include <stdlib.h>

char *DupInt(int num);
int *DupIntArray(const int *arr, int size);
int main(){

    int original = 3;
    char *copy = DupInt(original);

    if (copy != NULL)
    {
        printf("Original: %d\n", original);
        printf("Copy: %s\n", copy);

        // Remember to free the allocated memory when done
        free(copy);
    }
    else
    {
        printf("Failed to duplicate the string.\n");
    }   

    int originalArray[] = { 1, 2, 3, 4, 5 };
    int size = sizeof(originalArray) / sizeof(originalArray[0]);

    int *copyArray = DupIntArray(originalArray, size);

    if (copyArray != NULL)
    {
        printf("Original array: ");
        for (int i = 0; i < size; i++)
        {
            printf("%d ", originalArray[i]);
        }
        printf("\n");

        printf("Copy array: ");
        for (int i = 0; i < size; i++)
        {
            printf("%d ", copyArray[i]);
        }
        printf("\n");

        // Remember to free the allocated memory when done
        free(copyArray);
    }
    else
    {
        printf("Failed to duplicate the array.\n");
    }

    return 0;
}
char *DupInt(int num) {
    // Determine the number of digits in the integer
    int numDigits = snprintf(NULL, 0, "%d", num);

    // Allocate memory for the new string (including space for the null terminator)
    char *duplicate = (char *)malloc((numDigits + 1) * sizeof(char));

    if (duplicate == NULL) {
        return NULL; // Memory allocation failed
    }

    // Convert the integer to a string and copy each character to the new string
    snprintf(duplicate, numDigits + 1, "%d", num);

    return duplicate;
}

int *DupIntArray(const int *arr, int size)
{
    if (arr == NULL || size <= 0)
    {
        return NULL; // Handle NULL input array or invalid size
    }

    // Allocate memory for the new int array
    int *duplicate = (int *)malloc(size * sizeof(int));

    if (duplicate == NULL)
    {
        return NULL; // Memory allocation failed
    }

    // Copy each element from the original array to the new array
    for (int i = 0; i < size; i++)
    {
        duplicate[i] = arr[i];
    }

    return duplicate;
}
