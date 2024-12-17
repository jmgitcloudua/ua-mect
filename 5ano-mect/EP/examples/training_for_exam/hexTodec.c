#include <stdio.h>
#include <math.h>

int HexToDec(char hex[])
{
    int dec = 0;
    int i = 0;
    int len = 0;
    while (hex[len] != '\0')
    {
        len++;
    }
    len--;
    while (hex[i] != '\0')
    {
        // get the remainder of n divided by 10
        // multiply it by 2 to the power of i and add it to dec
        // divide n by 10
        // increment i
        if (hex[i] >= '0' && hex[i] <= '9')
        {
            dec += (hex[i] - '0') * pow(16, len);
        }
        else if (hex[i] >= 'A' && hex[i] <= 'F')
        {
            dec += (hex[i] - 'A' + 10) * pow(16, len);
        }
        else if (hex[i] >= 'a' && hex[i] <= 'f')
        {
            dec += (hex[i] - 'a' + 10) * pow(16, len);
        }
        else
        {
            printf("Invalid hexadecimal input.");
            return 0;
        }
        len--;
        i++;
    }
    return dec;
}

int main()
{
    char hex[100];
    printf("Enter a hexadecimal number: ");
    //scanf("%d", &n);
    if (scanf("%s", hex) != 1)
    {
        // Handle input error, for example:
        fprintf(stderr, "Error: Failed to read an integer.\n");
        return 1; // Return an error code
    }
    printf("%s in Hexadecimal = %d in Decimal \n", hex, HexToDec(hex));

    return 0;
}