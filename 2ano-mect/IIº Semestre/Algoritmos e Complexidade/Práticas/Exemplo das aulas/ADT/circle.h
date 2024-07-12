/*ADT:Circle*/
/*Module of Dependencies*/
#include "point.h"
/*Exported Type*/
typedef struct circle Circle;

//Constructors and Destructors
Circle *createCircle(float x, float y, float r); // create circle with a center(x,y) and r radius
void freeCircle(Circle *c);                      // frees memory of point early created

// Accessors and Modifiers(get and se
float getRadius(Circle *c);  // get Radius
Point *getCenter(Circle *c); // get center

//Functions and Operators
float circleArea(Circle *c);            // retrun the circle area
int verifyCircle(Circle *c, Point *p); //verify if point is in circle
