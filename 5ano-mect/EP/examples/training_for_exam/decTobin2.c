#include <stdio.h>
#include <math.h>

void DecToBin(int n)
{
    int bin[32];
    int i = 0;
    while (n > 0)
    {
        // storing remainder in binary array
        // divde n by 2
        // increment i
        bin[i] = n % 2;
        n /= 2;
        i++;
    }
    // printing binary array in reverse order
    for (int j = i - 1; j >= 0; j--)
        printf("%d", bin[j]);
}

int main()
{
    int n;
    printf("Enter a decimal number: ");
    // scanf("%d", &n);
    if (scanf("%d", &n) != 1)
    {
        // Handle input error, for example:
        fprintf(stderr, "Error: Failed to read an integer.\n");
        return 1; // Return an error code
    }
    printf("%d in Decimal = ", n);
    DecToBin(n);
    printf(" in Binary\n");

    return 0;
}