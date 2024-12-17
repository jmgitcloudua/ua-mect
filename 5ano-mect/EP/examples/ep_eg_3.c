#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#include <time.h>

double randomDouble()
{
    return 2*(double)rand() / (double)RAND_MAX - 1;
}

int main()
{

    int interval = 10000; //srand(10);
    int circle_points = 0, square_points = 0;

    for (int i = 0; i < (interval * interval); i++)
    {
        double rand_x = randomDouble();
        double rand_y = randomDouble();

        if (sqrt(rand_x * rand_x + rand_y * rand_y) <= 1)
            circle_points++;

        square_points++;

        double pi = (double)(4 * circle_points) / square_points;

        if (i % interval == 0)
            printf("After %d iterations, Pi = %f \n", i, pi);
    }
}