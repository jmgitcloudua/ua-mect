/**
 * Nome Jodionisio da Lucinda João Muachifi
 * Nº Mec: 97147
 * Cadeira de : Algoritmo e Complexidade | 2º Ano-2º semestre
 * Curso: MIECT  
 * Abril 2021
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>


#include "Sorting.h"
#include "elapsed_time.h"

//Begin printArrays
void printForInts(void *p)
{
    assert(p != NULL);
    printf("%d", *(int *)p); // Casting to the appropriate pointer type
}
//---end printArrays

//Begin Swap
void swap(int *p, int *q)
{
    int tmp;
    tmp = *p;
    *p = *q;
    *q = tmp;
}
//---end Swap

//Begin Shell Sort
void shellSort(int a[], int n)
{

    assert(a != NULL && n != 0);

    for (int gap = n / 2; gap > 0; gap /= 2) // Gap sequence
        for (int i = gap; i < n; i++)        // Elements to be sorted
        {
            int tmp = a[i];
            int j = i; // Insertion sort
            for (; j >= gap && tmp < a[j - gap]; j -= gap)
                a[j] = a[j - gap];
            a[j] = tmp;
        }
}

//-----end Shell sort

// Begin Heap Sort
// heapify function is used to build the max heap
// max heap has maximum element at the root which means
// first element of the array will be maximum in max heap
void heapify(int Array[], int n, int i)
{
    int max = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    //if the left element is greater than root
    if (left <= n && Array[left] > Array[max])
    {
        max = left;
    }

    //if the right element is greater than root
    if (right <= n && Array[right] > Array[max])
    {
        max = right;
    }

    //if the max is not i
    if (max != i)
    {
        int temp = Array[i];
        Array[i] = Array[max];
        Array[max] = temp;
        //Recursively heapify the affected sub-tree
        heapify(Array, n, max);
    }
}
void heapSort(int Array[], int n)
{
    int temp;
    for (int i = n / 2; i >= 0; i--)
    {
        heapify(Array, n - 1, i);
    }
    for (int i = n - 1; i >= 0; i--)
    {
        //swap last element of the max-heap with the first element
        temp = Array[i];
        Array[i] = Array[0];
        Array[0] = temp;

        //exclude the last element from the heap and rebuild the heap
        heapify(Array, i - 1, 0);
    }
}
//----end Heap Sort

// Begin Selection Sort
void selectionSort(int a[], int n)
{
    for (int k = n - 1; k > 0; k--)
    {
        int indMax = 0;
        for (int i = 1; i <= k; i++)
        {
            if (a[i] >= a[indMax])
                indMax = i;
        }
        if (indMax != k)
            swap(&a[indMax], &a[k]);
    }
}
//---end Selection Sort

//Begin Bubble Sort
void bubbleSort2(int a[], int n)
{
    int k = n;
    int stop = 0;
    while (stop == 0)
    {
        stop = 1;
        k--;
        for (int i = 0; i < k; i++)
            if (a[i] >= a[i + 1])
            {
                swap(&a[i], &a[i + 1]);
                stop = 0;
            }
    }
}
//---end Bubble Sort

//Begin Insertion Sort
void insertElement(int sorted[], int n, int elem)
{
    // sorted is sorted
    // there is space to add more element
    int i;
    for (i = n - 1; (i >= 0) && (elem < sorted[i]); i--)
    {
        sorted[i + 1] = sorted[i];
    }
    sorted[i + 1] = elem;
}
void insertionSort(int a[], int n)
{
    for (int i = 1; i < n; i++)
        if (a[i] < a[i - 1])
            insertElement(a, i, a[i]);
}
//---end Insertion Sort

//Begin Marge Sort
void mergeListSort(int seq[], unsigned int start, unsigned int middle, unsigned int end)
{
    unsigned int inica = start, inicb = middle + 1, indi = 0, indc;
    /*Memory attribution to household */
    int *seqtemp = (int *)calloc(end - start + 1, sizeof(int));
    while (inica <= middle && inicb <= end)
        if (seq[inica] < seq[inicb])
            seqtemp[indi++] = seq[inica++]; //element of the first part
        else
            seqtemp[indi++] = seq[inicb++]; //element of the second part
    /*Copy the rest elements of the first part of the array*/
    while (inica <= middle)
        seqtemp[indi++] = seq[inica++];
    /*Copy the rest elements of the second part of the array*/
    while (inicb <= end)
        seqtemp[indi++] = seq[inicb++];
    /*Copy the result to sort the array*/
    for (indc = 0, inica = start; indc < indi; indc++, inica++)
        seq[inica] = seqtemp[indc];
    free(seqtemp); // freeing the local household memory
}
void mergeSort(int seq[], unsigned int start, unsigned int end)
{
    unsigned int middle;
    if (start < end) /* stop condition */
    {
        middle = (start + end) / 2; /* divide array */
        /* recursive call to sort the first half array*/
        mergeSort(seq, start, middle);
        /* recursive call to sort the second half array*/
        mergeSort(seq, middle + 1, end);
        /*merge the two of half sorted arrat*/
        mergeListSort(seq, start, middle, end);
    }
}
//--- end Merge Sort
int main(int argc, char const *argv[])
{
    (void)elapsed_time();
    int array[] = {81, 94, 11, 96, 12, 35, 17, 95, 28, 58, 41, 75, 15, 201, 99, 48, 300, 225, 101, 120};
    printf("\t\tArray not sorted\t\n");
    printArray(array, 20, sizeof(int), printForInts);
    //-------------------------------------------
    printf("\t\tArray sorted(Shell Sort)\t\n");
    shellSort(array, sizeof(array) / sizeof(*array));
    printArray(array, 20, sizeof(int), printForInts);
    double exeTime1 = elapsed_time() * 1000;
    printf("Time to take sort:  %10f ms\n", exeTime1);
    //---------------------------------------------
    printf("\t\tArray sorted(Heap Sort)\t\n");
    heapSort(array, sizeof(array) / sizeof(array[0]));
    printArray(array, 20, sizeof(int), printForInts);
    double exeTime2 = elapsed_time() * 1000;
    printf("Time to take sort:  %10f ms\n", exeTime2);
    //----------------------------------------------
    printf("\t\tArray sorted(Selection Sort)\t\n");
    selectionSort(array, sizeof(array) / sizeof(array[0]));
    printArray(array, 20, sizeof(int), printForInts);
    double exeTime3 = elapsed_time() * 1000;
    printf("Time to take sort:  %10f ms\n", exeTime3);
    //----------------------------------------------
    printf("\t\tArray sorted(Buble Sort)\t\n");
    bubbleSort2(array, sizeof(array) / sizeof(array[0]));
    printArray(array, 20, sizeof(int), printForInts);
    double exeTime4 = elapsed_time() * 1000;
    printf("Time to take sort:  %10f ms\n", exeTime4);
    //----------------------------------------------
    printf("\t\tArray sorted(Insertion Sort)\t\n");
    insertionSort(array, sizeof(array) / sizeof(array[0]));
    printArray(array, 20, sizeof(int), printForInts);
    double exeTime5 = elapsed_time() * 1000;
    printf("Time to take sort:  %10f ms\n", exeTime5);
    //----------------------------------------------
    printf("\t\tArray sorted(Merge Sort)\t\n");
    mergeSort(array, 0, sizeof(array) / sizeof(array[0]) - 1);
    printArray(array, 20, sizeof(int), printForInts);
    double exeTime6 = elapsed_time() * 1000;
    printf("Time to take sort:  %10f ms\n", exeTime6);

    return 0;
}
