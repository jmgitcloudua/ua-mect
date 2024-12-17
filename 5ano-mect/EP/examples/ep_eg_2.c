#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>

// return max of two numbers
int max(int a, int b){
    if (a > b)
    {
        return a;
    }
    return b;
    // return a > b ? a : b;
}

double randomDouble() {
    return (double)rand() / (double)RAND_MAX;
}

int main(){
    int a = -1;
    int b = 7;

    if (a > 0 && b++)
    {
        printf("Hello\n");
    }
    printf("b = %d\n", b); // b = 7

    printf("-------------\n");

    int c = 10;
    int d = c++ - 5; //+cc - 5 = 11 - 5 = 6 and c++ - 5 = 10 - 5 = 5
    printf("d = %d\n", d);

    printf("-------------\n");

    int e = max(10, 5);
    printf("e = %d\n", e);

    printf("-------------\n");

     int interval = 1000000;
    int circle_points = 0, square_points = 0;

    for (int i = 0; i < (interval * interval); i++) {
        double rand_x = randomDouble();
        double rand_y = randomDouble();

        if (rand_x * rand_x + rand_y * rand_y <= 1)
            circle_points++;

        square_points++;

        double pi = (double)(4 * circle_points) / square_points;

        if(i % interval == 0)
            printf("After %d iterations, Pi = %f \n", i, pi);
    }
}