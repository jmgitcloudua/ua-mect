#include <stdio.h>
#include <math.h>

int DecToBin(int n)
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
    printf("Enter a decimal number: ");
    //scanf("%d", &n);
    if (scanf("%d", &n) != 1)
    {
        // Handle input error, for example:
        fprintf(stderr, "Error: Failed to read an integer.\n");
        return 1; // Return an error code
    }
    printf("%d in Decimal = %d in Binary \n", n, DecToBin(n));

    return 0;
}