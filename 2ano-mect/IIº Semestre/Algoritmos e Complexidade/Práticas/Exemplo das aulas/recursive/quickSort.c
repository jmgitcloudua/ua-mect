/**
 * Nome Jodionisio da Lucinda João Muachifi
 * Nº Mec: 97147
 * Cadeira de : Algoritmo e Complexidade | 2º Ano-2º semestre
 * Curso: MIECT  
 * Abril 2021
 */
#include <stdio.h>
#include <stdlib.h>

void swap(int *p, int *q)
{
    int tmp;
    tmp = *p;
    *p = *q;
    *q = tmp;
}
void quickSort(int *A, int left, int right)
{
    //Base case
    if (left >= right)
    {
        return;
    }

    //Recursive case
    //Partion of phase
    int pivot = (left + right) / 2;
    int i = left;
    int j = right;

    do
    {
        while (A[i] < A[pivot])
        {
            i++;
        }
        while (A[j] > A[pivot])
        {
            j--;
        }

        if (i <= j)
        {
            swap(&A[i], &A[j]);
            i++;
            j--;
        }

    } while (i <= j);

    // Recursive call
    quickSort(A, left, j);
    quickSort(A, i, right);
}
void printArray(int seq[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf(" %d ", seq[i]);
    }
    printf("\n");
}
int main(int argc, char const *argv[])
{
    int A[] = {6, 5, 4 ,3 ,2 ,1,8,10,20,40,80,100};
    int size = sizeof(A) / sizeof(A[0]);
    printf("\tArray not sorted\n");
    printArray(A, size);
    //------------------------------------------
    printf("\tArray sorted(Quick Sort)\n");
    quickSort(A, 0, size - 1);
    printArray(A, size);
    return 0;
}
