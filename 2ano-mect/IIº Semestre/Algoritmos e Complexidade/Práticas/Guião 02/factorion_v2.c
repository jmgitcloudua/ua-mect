#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

static int numMult = 0;
static int numDiv = 0;

int sumDigitsFact(int n, int B)
{

    assert(n >= 0);
    assert(B <= 13); // not need for larger bases(with 32bit ints)

    //create the factoriaç LUT
    static int factorial[13] = {1};
    static int lastd = 0; //last digit whose factorial is stored
    while (lastd < B - 1) // This loop runs only on the first call
    {
        lastd++;
        factorial[lastd] = factorial[lastd - 1] * lastd;
        numMult += 1;
    }
    //compute the sum of factorials
    int sum = 1;
    if (n != 0)
    {
        sum = 0;
        while (n > 0)
        {
            int d = n % B;
            n /= B;
            sum += factorial[d];
            numDiv += 2;
        }
    }
    return sum;
}

int main(int argc, char const *argv[])
{
    printf("---------------------------------------\n");
    printf("| Factorion numbers smaller than 10^6 |\n");
    printf("---------------------------------------\n\n| ");
    int B = 10;
    if (argc > 1)
    {
        B = atoi(argv[1]);
    }
    for (int n = 0; n < 1000000; n++)
    {
        if (n == sumDigitsFact(n, B))
        {
            printf("%d | ", n);
        }
    }
    printf("\n");
    printf("numMult = %d\n", numMult);
    printf("numDiv = %d\n", numDiv);

    return 0;
}
