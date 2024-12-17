#include <stdio.h>

int factorial(int n);

int main()
{
    int n;
    printf("Enter a positive integer: ");
    if(scanf("%d", &n) != 1)
    {
        printf("Invalid input");
        return 1;
    }
    printf("Factorial of %d! = %d\n", n, factorial(n));
    return 0;
}


int factorial(int n)
{
    if (n == 0)
        return 1;
    else
        return (n * factorial(n - 1));
}