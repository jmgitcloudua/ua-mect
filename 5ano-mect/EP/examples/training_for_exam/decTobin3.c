// #include <stdio.h>
// #include <math.h>

// char *DecToBin(unsigned int num)
// {
//     static char bin[33];
//     int i = 0;
//     while (num != 0)
//     {
//         // get the remainder of n divided by 2
//         // multiply it by 2 to the power of i and add it to bin
//         // divide n by 2
//         // increment i
//         bin[i] = (num % 2) + '0';
//         num /= 2;
//         i++;
//     }
//     bin[i] = '\0';
//     return bin;
// }

// int main()
// {
//     unsigned int num;
//     printf("Enter a decimal number: ");
//     //scanf("%d", &n);
//     if (scanf("%u", &num) != 1)
//     {
//         // Handle input error, for example:
//         fprintf(stderr, "Error: Failed to read an integer.\n");
//         return 1; // Return an error code
//     }
//     printf("%u in Decimal = %s in Binary \n", num, DecToBin(num));

//     return 0;
// }
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *DecToBin(unsigned int num);
unsigned int BinToDec(const char *binaryString);
unsigned int BinToDec2(const char *binStr);

int main(void)
{
    unsigned int num;
    printf("Enter a decimal number: ");
    if (scanf("%u", &num) != 1)
    {
        // Handle input error, for example:
        fprintf(stderr, "Error: Failed to read an integer.\n");
        return 1; // Return an error code
    }
    printf("%u in Decimal = %s in Binary \n", num, DecToBin(num));

    char binaryString[33];
    printf("Enter a binary number: ");
    if (scanf("%32s", binaryString) != 1)
    {
        // Handle input error, for example:
        fprintf(stderr, "Error: Failed to read a string.\n");
        return 1; // Return an error code
    }
    printf("%s in Binary = %u in Decimal \n", binaryString, BinToDec(binaryString));

    char binaryString2[33];
    printf("Enter a binary number: ");
    if (scanf("%32s", binaryString2) != 1)
    {
        // Handle input error, for example:
        fprintf(stderr, "Error: Failed to read a string.\n");
        return 1; // Return an error code
    }
    printf("%s in Binary = %u in Decimal \n", binaryString2, BinToDec2(binaryString2));

    return 0;
}

char *DecToBin(unsigned int num)
{
    // Calculate the number of bits in an unsigned int
    size_t numBits = sizeof(unsigned int) * 8;

    // Allocate memory for the binary string
    char *binaryString = (char *)malloc(numBits + 1); // +1 for the null terminator

    if (binaryString == NULL)
    {
        // Memory allocation failed
        return NULL;
    }

    // Convert the decimal to binary representation
    for (size_t i = 0; i < numBits; ++i)
    {
        binaryString[numBits - 1 - i] = (num & (1 << i)) ? '1' : '0';
    }

    // Null-terminate the string
    binaryString[numBits] = '\0';

    return binaryString;
}

// Convert a binary to decimal number
// unsigned int BinToDec(const char *binaryString) {
//     unsigned int num = 0;

//     // Calculate the number of bits in an unsigned int
//     size_t numBits = sizeof(unsigned int) * 8;

//     // Convert the binary string to decimal representation
//     for (size_t i = 0; i < numBits; ++i) {
//         num += (binaryString[numBits - 1 - i] - '0') << i;
//     }

//     return num;
// }
unsigned int BinToDec(const char *binaryString)
{
    if (binaryString == NULL)
    {
        // Handle NULL input
        return 0;
    }

    // Initialize the result to 0
    unsigned int result = 0;

    // Iterate through each character in the binary string
    while (*binaryString != '\0')
    {
        // Multiply the current result by 2 (left shift) and add the current bit
        result = result * 2 + (*binaryString - '0');
        // Move to the next character in the binary string
        ++binaryString;
    }

    return result;
}
// or
unsigned int BinToDec2(const char *binStr)
{

    if (binStr == NULL)
    {
        return 0;
    }

    unsigned int dec = 0;
    int length = strlen(binStr);

    for (int i = 0; i < length; i++)
    {
        if (binStr[i] == '1')
        {
            dec |= (1U << (length - 1 - i));
        }
        else if (binStr[i] != '0')
        {
            return 0;
        }
    }
    return dec;
}