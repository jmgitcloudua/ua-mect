#include <stdio.h>
#include <stdlib.h>

char *DupFloat(float num);
float *DupFloatArray(const float *arr, int size);

int main(){

   float original = 3.14159;
   char *copy = DupFloat(original);

    if (copy != NULL)
    {
        printf("Original: %f\n", original);
        printf("Copy: %s\n", copy);

        // Remember to free the allocated memory when done
        free(copy);
    }
    else
    {
        printf("Failed to duplicate the string.\n");
    }

    float arr[] = {1.1, 2.2, 3.3, 4.4, 5.5};
    int size = sizeof(arr) / sizeof(arr[0]);

    float *duplicate = DupFloatArray(arr, size);

    if (duplicate != NULL)
    {
        printf("Original array: ");
        for (int i = 0; i < size; i++)
        {
            printf("%.2f ", arr[i]);
        }
        printf("\n");

        printf("Duplicate array: ");
        for (int i = 0; i < size; i++)
        {
            printf("%.2f ", duplicate[i]);
        }
        printf("\n");

        // Remember to free the allocated memory when done
        free(duplicate);
    }
    else
    {
        printf("Failed to duplicate the array.\n");
    }


    return 0;
}
char *DupFloat(float num) {
    // Convert the float number to a string representation
    int bufferSize = snprintf(NULL, 0, "%f", num) + 1;
    char *str = (char *)malloc(bufferSize);
    
    if (str == NULL) {
        return NULL; // Memory allocation failed
    }

    snprintf(str, bufferSize, "%f", num);
    
    return str;
}

float *DupFloatArray(const float *arr, int size)
{
    if (arr == NULL || size <= 0)
    {
        return NULL; // Handle NULL input array or invalid size
    }

    // Allocate memory for the new float array
    float *duplicate = (float *)malloc(size * sizeof(float));

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