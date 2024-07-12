#include <stdio.h>

// Function to remove duplicate elements
// This function returns new size of modified
// array.
/*int removeDuplicates(int arr[], int n)
{
    // Return, if array is empty
    // or contains a single element
    if (n == 0 || n == 1)
        return n;

    int temp[n];

    // Start traversing elements
    int j = 0;
    for (int i = 0; i < n - 1; i++)

        // If current element is not equal
        // to next element then store that
        // current element
        /*&& arr[i] % arr[i+1] == 0*/
/*if (arr[i] != arr[i + 1] )
        {
            temp[j++] = arr[i];
        }
    // Store the last element as whether
    // it is unique or repeated, it hasn't
    // stored previously
    temp[j++] = arr[n - 1];

    // Modify original array
    for (int i = 0; i < j; i++)
    {   
            arr[i] = temp[i];   
    }
    return j;
}*/
void swap(int *p, int *q)
{
    int tmp;
    tmp = *p;
    *p = *q;
    *q = tmp;
}
void removeDuplicates(int *arr, int *n)
{

    int k = 0;

    // iterate each element of arr[]
    for (int i = 0; i < *(n); ++i)
    {

        // checking if there exist an element arr[j] ( j < i )
        // that is equal to arr[i]
        int flag = 1;
        for (int j = 0; j < i; ++j)
        {
            if ((arr[j] == arr[i]) || (arr[j] > arr[i+1] && arr[j] % arr[i+1] == 0))
            {
                flag = 0;
                break;
            }
        }

        // flag == 0 means arr[i] is repeated
        // flag == 1 means that no element that appears
        // on left side of arr[i] is equal to arr[i]
        // therefore, we swap arr[k] and arr[i] then increment k
        if (flag)
            swap(&arr[k++], &arr[i]);
    }

    *(n) = k;
}
int main(int argc, char const *argv[])
{
    int arr[] = {1, 2, 2, 3, 4, 4, 4, 5, 5, 5};
    int a1[] = {2, 2, 2, 3, 3, 4, 5, 8, 8, 9}; // result should be {2,3,5}
    int a2[] = {7, 8, 2, 2, 3, 3, 3, 8, 8, 9}; // result should be {7,8,3}
    int n = sizeof(arr) / sizeof(arr[0]);

    // removeDuplicates() returns new size of
    // array.
    removeDuplicates(a2, &n);

    // Print updated array
    for (int i = 0; i < n; i++)
    {
        printf(" %d ", a2[i]);
    }

    printf("\n");
    return 0;
}
