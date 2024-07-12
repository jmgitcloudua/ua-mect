#include <stdio.h>
#include <math.h>
#include "circle.h"
#include "listOfCrircle.h"

int main(void)
{
    Circle *c1 = createCircle(0, 0, 1);
    Circle *c2 = createCircle(1, 1, 1);
    Circle *c3 = createCircle(2, 2, 3);
    Element *list = NULL;
    list = insertList(list, c3);
    list = insertList(list, c2);
    list = insertList(list, c1);
    printf("List Of Circle:\n");
    pritnList(list);
    printf("Total Area: %.3f\n", sumOfAreaList(list));

    return 0;
}
