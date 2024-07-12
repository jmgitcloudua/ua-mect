#include <stdio.h>
#include <stdlib.h>
#include "listOfCrircle.h"
#include "circle.h"
#include "point.h"

Element *insertList(Element *list, Circle *c)
{
    Element *p = (Element *)malloc(sizeof(Element));
    p->info = c;
    p->prox = list;
    return p;
}
void printList(Element *list)
{
    float x, y, radius;
    Point *center;
    Element *p = list;
    while (p != NULL)
    {
        center = getCenter(p->info);
        getPoint(center, &x, &y);
        radius = getRadius(p->info);
        printf("Center: (%.3f,%.3f) radius: %.3f\n", x, y, radius);
        p = p->prox;
    }
}
void freeList(Element *list)
{
    Element *p = list, *t;
    while (p != NULL)
    {
        t = p->prox;
        freeCircle(p->info);
        free(p);
        p = t;
    }
}
float sumOfAreaList(Element * list)
{
    Element *p = list;
    float area = 0.0;
    while (p != NULL)
    {
        area += circleArea(p->info);
        p = p->prox;
    }
    return area;
}
