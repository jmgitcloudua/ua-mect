/********** Interface da Estrutura de Dados do Agregado **********/
/* Nome: elemento.h */
/* DefiniÁ„o do tipo dos elementos do agregado e das funÁıes de comparaÁ„o necess·rias. Este ficheiro deve ser modificado para 
adequar a definiÁ„o e as funÁıes a cada implementaÁ„o especÌfica. */
#include <string.h>
#ifndef _ELEMENTO
#define _ELEMENTO
    /************* DefiniÁ„o do Tipo de Dados do Elemento *************/
    typedef struct
{
    unsigned int dia;
    unsigned int mes;
    unsigned int ano;
} TData;
typedef struct
{
    unsigned int nreg;
    char nome[60];
    TData data;
} TElem;
/***** DefiniÁ„o do Tipo Ponteiro para a FunÁ„o de ComparaÁ„o *****/
typedef int (*PtFComp)(TElem, TElem);
/******* DefiniÁ„o das FunÁıes de ComparaÁ„o dos Elementos *******/
int CompNRegisto(TElem a, TElem b)
{
    if (a.nreg > b.nreg)
        return 1;
    else if (a.nreg < b.nreg)
        return -1;
    else
        return 0;
}
int CompNome(TElem a, TElem b)
{
    int comp = strcmp(a.nome, b.nome);
    if (comp > 0)
        return 1;
    else if (comp < 0)
        return -1;
    else
        return 0;
}
int CompData(TElem a, TElem b)
{
    if (a.data.ano > b.data.ano)
        return 1;
    else if (a.data.ano < b.data.ano)
        return -1;
    else if (a.data.mes > b.data.mes)
        return 1;
    else if (a.data.mes < b.data.mes)
        return -1;
    else if (a.data.dia > b.data.dia)
        return 1;
    else if (a.data.dia < b.data.dia)
        return -1;
    else
        return 0;
}
#endif