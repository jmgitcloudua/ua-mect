#include "circle.h"

struct element
{
    Circle * info;
    struct element * prox;
};

typedef struct element Element;

Element * insertList(Element * list, Circle * c);
void pritnList(Element * list);
float sumOfAreaList(Element * list);
void freeList(Element * list);
