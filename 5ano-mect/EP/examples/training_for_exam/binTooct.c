#include <stdio.h>
#include <math.h>

int BinToOctal(int n)
{
    int octal = 0;
    int i = 0;
    while (n != 0)
    {
        // get the remainder of n divided by 10
        // multiply it by 2 to the power of i and add it to octal
        // divide n by 10
        // increment i
        octal += (n % 10) * pow(8, i);
        n /= 10;
        i++;
    }
    return octal;
}

int main()
{
    int n;
    printf("Enter a binary number: ");
    //scanf("%d", &n);
    if (scanf("%d", &n) != 1)
    {
        // Handle input error, for example:
        fprintf(stderr, "Error: Failed to read an integer.\n");
        return 1; // Return an error code
    }
    printf("%d in Binary = %d in Octal \n", n, BinToOctal(n));

    return 0;
}