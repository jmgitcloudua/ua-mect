/**
 * Nome Jodionisio da Lucinda João Muachifi
 * Nº Mec: 97147
 * Cadeira de : Algoritmo e Complexidade | 2º Ano-2º semestre
 * Curso: MIECT  
 * Abril 2021
 */
#include <assert.h>
#include <stdio.h>

#include "Sorting.h"
#include "elapsed_time.h"

void heapBottomUp(int a[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--) // For each element that not failure , reposition it if necessary
        fixHeap(a, i, n);
}
void fixHeap(int a[], int index, int n)
{
    int child, tmp;
    for (tmp = a[index]; leftChild(index) < n; index = child)
    {
        child = leftChild(index); // The largest
        if (child != (n - 1) && a[child + 1] > a[child])
            child++; // moves up,
        if (tmp < a[child])
            a[index] = a[child]; // if needed
        else
            break;
    }
    a[index] = tmp; // Final position
}
void heapSort(int a[], int n)
{
    heapBottomUp(a, n);
    for (int i = n - 1; i > 0; i--)
    {
        swap(&a[0], &a[i]);
        fixHeap(a, 0, i); // only a[0] need to be repositioned
    }                     
}
int main(int argc, char const *argv[])
{
    /* code */
    return 0;
}
