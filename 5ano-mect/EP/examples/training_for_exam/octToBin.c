#include <stdio.h>
#include <math.h>

int OctToBin(int n)
{
    int bin = 0;
    int i = 1;
    while (n != 0)
    {
        // get the remainder of n divided by 2
        // multiply it by i and add it to bin
        // divide n by 2
        // multiply i by 10
        bin += (n % 2) * i;
        n /= 2;
        i *= 10;
    }
    return bin;
}

int main()
{
    int n;
    printf("Enter an octal number: ");
    //scanf("%d", &n);
    if (scanf("%d", &n) != 1)
    {
        // Handle input error, for example:
        fprintf(stderr, "Error: Failed to read an integer.\n");
        return 1; // Return an error code
    }
    printf("%d in Octal = %d in Binary \n", n, OctToBin(n));

    return 0;
}