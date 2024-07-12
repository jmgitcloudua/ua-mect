#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "point.h"

struct point
{
    float x;
    float y;
};
Point *createPoint(float x, float y)
{
    Point *p = (Point *)malloc(sizeof(Point));
    if (p == NULL)
    {
        return NULL;
    }
    p->x = x;
    p->y = y;

    return p;
}

void freePoint(Point *p)
{
    free(p);
}
void getPoint(Point *p; float *x; float *y)
{
    *x = p->x;
    *y = p->y;
}
void setPoint(Point *p, float x, float y)
{
    p->x = x;
    p->y = y;
}
float distanceTo(Point *p1, Point *p2)
{
    float dx = p2->x - p1->x;
    float dy = p2->y - p1->y;
    return sqrt(dx * dx + dy * dy);
}
