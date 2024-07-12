#include <stdio.h>

// Binary search 1.0
int recursiveBinarySearch(int seq[], unsigned int start, unsigned int end, int value)
{

    unsigned int  middle;

    if (start > end)
    {
        return -1; // stop condition in case of unsuccessful search
    }
    middle = (start + end)/2; //calculation of the average position
    
    if (seq[middle] == value) // stop condition in case of successful search
    {
        return middle;
    }

    if (seq[middle] > value)
    {
        /*recursive invocation for the first half of the aggregate*/
        recursiveBinarySearch(seq, start, middle - 1, value);
    }
    else
    {
        /*recursive invocation for the second half of the aggregate*/
        recursiveBinarySearch(seq, middle + 1, end, value);
    }
    
    

    
}
// Binary search version 2.0
int binarySearch(int seq[], int size, int value)
{
    int left = 0;
    int right = size  - 1;
    while (left <= right)
    {
        int middle = (left + right) / 2; // Divisão inteira
        if (seq[middle] == value)
            return middle;
        if (seq[middle] > value)
            right = middle - 1;
        else
            left = middle + 1;
    }
    return -1;
}
void printArray(int seq[], int size)
{
    int i = 0;
    for (i = 0; i < size; i++)
    {
        printf("%d\t", seq[i]);
    }
    printf("\n");
}
int main(int argc, char const *argv[])
{
    int seq[10] = {2, 4, 5, 6,  7, 8, 10, 12, 20, 30};
    unsigned int nelem = sizeof(seq) / sizeof(*seq);
    printf("Choice one value you want to search\n");
    printArray(seq, nelem);
    unsigned int n;
    printf("Value : ");
    scanf("%d", &n);
    unsigned int recBinarySearch = recursiveBinarySearch(seq, 0, nelem - 1, n);
    unsigned int binSearch = binarySearch(seq, nelem , n);
    printf("The value searched is in index(Binary Search(V1): %d\n", recBinarySearch);
    printf("The value searched is in index(Binary Search(V2): %d\n", binSearch);
    return 0;
}
