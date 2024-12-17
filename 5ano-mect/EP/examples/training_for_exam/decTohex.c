// #include <stdio.h>
// #include <math.h>

// int DecToHex(int n)
// {
//     int hex = 0;
//     int i = 0;
//     while (n != 0)
//     {
//         // get the remainder of n divided by 16
//         // multiply it by 2 to the power of i and add it to hex
//         // divide n by 16
//         // increment i
//         hex += (n % 16) * pow(10, i);
//         n /= 16;
//         i++;
//     }
//     return hex;
// }

// int main()
// {
//     int n;
//     printf("Enter a decimal number: ");
//     //scanf("%d", &n);
//     if (scanf("%d", &n) != 1)
//     {
//         // Handle input error, for example:
//         fprintf(stderr, "Error: Failed to read an integer.\n");
//         return 1; // Return an error code
//     }
//     printf("%d in Decimal = %d in Hexadecimal \n", n, DecToHex(n));

//     return 0;
// }
#include <stdio.h>
#include <math.h>

// Function to convert decimal to hexadecimal
void DecToHex(int n)
{
    char hex[100];
    int i = 0;

    // Handle the special case when n is 0
    if (n == 0)
    {
        printf("0 in Decimal = 0 in Hexadecimal\n");
        return;
    }

    // Convert decimal to hexadecimal
    while (n != 0)
    {
        int remainder = n % 16;

        // Convert remainder to hexadecimal character
        if (remainder < 10)
            hex[i] = remainder + '0';
        else
            hex[i] = remainder - 10 + 'A';

        n /= 16;
        i++;
    }

    // Print the result in reverse order
    printf("%d in Decimal = 0x", n);  // Fix the format specifier
    for (int j = i - 1; j >= 0; j--)
        printf("%c", hex[j]);
    printf(" in Hexadecimal\n");
}

int main()
{
    int n;
    printf("Enter a decimal number: ");
    if (scanf("%d", &n) != 1)
    {
        // Handle input error
        fprintf(stderr, "Error: Failed to read an integer.\n");
        return 1; // Return an error code
    }

    DecToHex(n);

    return 0;
}
