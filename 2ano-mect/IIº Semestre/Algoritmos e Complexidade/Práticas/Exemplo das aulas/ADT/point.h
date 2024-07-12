/* ADT: Point 2D*/

typedef struct point Point; // exported type

//Constructors and Destructors
Point * createPoint(float x, float y); // create poit (x,y). Return NULL if there is no memory
void freePoint(Point * p);             // frees memory of point early created

// Accessors and Modifiers(get and set)
void getPoint(Point * p, float * x, float * y); // retturn the coordinates points
void setPoint(Point * p, float  x, float  y); // put ou assings  new values to the coordinates points

//Functions and Operators
float distanceTo(Point * p1, Point * p2); // return a distance between two points