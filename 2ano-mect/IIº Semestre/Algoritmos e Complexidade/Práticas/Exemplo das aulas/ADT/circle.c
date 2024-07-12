#include <stdlib.h>
#include "circle.h"

#define PI 3.14159

struct circle
{
    Point *p;
    float r;
};

Circle *createCircle(float x, float y, float r)
{
    Circle *c = (Circle *)malloc(sizeof(Circle));
    if (c != NULL)
    {
        c->p = createPoint(x, y);
        if (c->p == NULL)
        {
            return NULL;
        }
        c->r = r;
    }
    return c;
}
void freeCircle(Circle *c)
{
    freePoint(c->p);
    free(c);
}
float getRadius(Circle *c)
{
    return c->r;
}
Point *getCenter(Circle *c)
{
    return c->p;
}
float circleArea(Circle *c)
{
    return PI * c->r * c->r;
}
int verifyCircle(Circle *c, Point *p)
{
    float d = distanceTo(c->p, p);
    return (d < c->r);
}