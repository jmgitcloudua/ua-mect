#include <stdio.h>
#include <stdlib.h>
#include "elemento.h" /* caracterizaÁ„o do tipo elemento */
#define CRESCENTE 1
#define DECRESCENTE -1
void SwapElementos(TElem *, TElem *);
void Sequential_Sort(TElem[], unsigned int, PtFComp, int);
void Display(TElem[], unsigned int);
int main(void)
{
    TElem pintores[] = {
        {1, "Vincent Van Gogh", {30, 3, 1853}},
        {2, "Vieira da Silva", {13, 6, 1908}},
        {3, "Amedeo Modigliani", {12, 7, 1884}},
        {4, "Claude Monet", {14, 11, 1840}},
        {5, "Georgia O'Keeffe", {15, 11, 1887}}};
    int nelem = sizeof(pintores) / sizeof(pintores[0]);
    /* ponteiro para a funÁ„o de comparaÁ„o inicializado a NULL */
    PtFComp fcomp = NULL;
    fcomp = CompNome; /* ordenaÁ„o alfabÈtica ascendente */
    Sequential_Sort(pintores, nelem, fcomp, CRESCENTE);
    printf("Ascending Alphabetical Order\n");
    Display(pintores, nelem);
    fcomp = CompData; /* ordenaÁ„o cronolÛgica decrescente */
    Sequential_Sort(pintores, nelem, fcomp, DECRESCENTE);
    printf("Sort the Descending Chronological\n");
    Display(pintores, nelem);
    fcomp = CompNRegisto; /* ordenaÁ„o crescente por registo */
    Sequential_Sort(pintores, nelem, fcomp, CRESCENTE);
    printf("Ascending Numerical Sorting\n");
    Display(pintores, nelem);
    return EXIT_SUCCESS;
}
void Sequential_Sort(TElem seq[], unsigned int nelem,PtFComp fcomp, int tord)
{
    unsigned int indi, indj;
    for (indi = 0; indi < nelem - 1; indi++)
        for (indj = indi + 1; indj < nelem; indj++)
            if (fcomp(seq[indi], seq[indj]) == tord)
                SwapElementos(&seq[indi], &seq[indj]);
}
void SwapElementos(TElem *x, TElem *y)
{
    TElem temp;
    temp = *x;
    *x = *y;
    *y = temp;
}
void Display(TElem seq[], unsigned int nelem){
    for (int i = 0; i < nelem; i++)
    {
        printf(" %d, %s, %02d/%02d/%02d \n", seq[i].nreg, seq[i].nome, seq[i].data.dia,seq[i].data.mes,seq[i].data.ano);
    }
    //printf("\n");
    
}