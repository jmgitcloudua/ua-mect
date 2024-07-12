/**
 * Nome Jodionisio da Lucinda João Muachifi
 * Nº Mec: 97147
 * Cadeira de : Algoritmo e Complexidade | 2º Ano-2º semestre
 * Curso: MIECT  
 * Abril 2021
 */
#include <stdio.h>
#include <assert.h>

void trocar(int *p, int *q)
{
    int tmp;
    tmp = *p;
    *p = *q;
    *q = tmp;
}
void inverter(int *v, int esq, int dir)
{
    if (esq < dir)
    {
        trocar(&v[esq], &v[dir]);
        inverter(v, esq + 1, dir - 1);
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
    int seq[] = {1, 2 ,3, 4, 5, 6 , 7 , 8 , 9 ,10};
    unsigned int size = sizeof(seq) / sizeof(*seq);
    printf("\tArray not invrted\n");
    printArray(seq, size);
    //------------------
    printf("\tArray inverted\n");
    inverter(seq, 0, size - 1);
    printArray(seq, size);

    return 0;
}
