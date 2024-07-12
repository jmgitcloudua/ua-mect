/**
 * Nome Jodionisio da Lucinda João Muachifi
 * Nº Mec: 97147
 * Cadeira de : Algoritmo e Complexidade | 2º Ano-2º semestre
 * Curso: MIECT  
 * Abril 2021
 */
#include <stdio.h>

int sequentialSearch(int a[], int index, int size, int value)
{ //or linear seacrh

    if (size < index)
    {
        return -1;
    }
    if (a[index] == value)
    {
        return index;
    }
    if (a[size] == value)
    {
        return size;
    }

    return sequentialSearch(a, index + 1, size - 1, value);
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
    int seq[] = {4, 2, 8, 100, 40, 80, 120, 220, 16, 10};
    unsigned int size = sizeof(seq) / sizeof(*seq);
    printf("Choice one value you want to search\n");
    printArray(seq, size);
    printf("Value : ");
    unsigned int n;
    scanf("%d", &n);
    unsigned int index = sequentialSearch(seq, 0, size - 1, n);
    if (index != -1)
        printf("Element %d is present at index %d\n", n, index);
    else
        printf("Element %d is not present\n", n);

    return 0;
}
