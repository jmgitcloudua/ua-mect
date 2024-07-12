/**
 * Nome Jodionisio da Lucinda João Muachifi
 * Nº Mec: 97147
 * Cadeira de : Algoritmo e Complexidade | 2º Ano-2º semestre
 * Curso: MIECT  
 * Abril 2021
 */
#include <stdio.h>
#include <stdlib.h>

void merge(int *A, int *tmpA, int lPos, int rPos, int rEnd)
{
    int lEnd = rPos - 1;
    int tmpPos = lPos;
    int nElements = rEnd - lPos + 1;

    //compare the 1st element of each half
    //and copy it sortly to a temporary array

    while (lPos <= lEnd && rPos <= rEnd)
    {
        if (A[lPos] <= A[rPos])
        {
            tmpA[tmpPos++] = A[lPos++];
        }
        else
        {
            tmpA[tmpPos++] = A[rPos++];
        }
        for (int i = 0; i < nElements; i++, rEnd--)
        {
            A[rEnd] = tmpA[rEnd];
        }
    }
}
void mergeSorte(int *A, int *tmpA, int left, int right)
{
    //More than one element?
    if (left < right)
    {
        int center = (left + right) / 2;
        mergeSorte(A, tmpA, left, center);
        mergeSorte(A, tmpA, center + 1, right);
        merge(A, tmpA, left, center + 1, right);
    }
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
    int B[12] ;
    printf("\t\tArray not sorted\n");
    printArray(A, size);
    //------------------------------------------
    printf("\t\tArray sorted(Merge Sort)\n");
    mergeSorte(A, B, 0, size - 1);
    printArray(A, size);
    return 0;
}
