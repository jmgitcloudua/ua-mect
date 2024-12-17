#include <stdio.h>

int gcd(int a, int b);
int lcm(int a, int b);

int main()
{
    int a, b;
    printf("Enter two positive integers: ");
    if (scanf("%d %d", &a, &b) != 2)
    {
        printf("Invalid input");
        return 1;
    }
    printf("GCD of %d and %d = %d\n", a, b, gcd(a, b));
    printf("LCM of %d and %d = %d\n", a, b, lcm(a, b));
    return 0;
}
// Greatest common divisor
int gcd(int a, int b)
{
    if (b != 0)
        return gcd(b, a % b);
    else
        return a;
}
// Least common multiple
int lcm(int a, int b)
{
    return (a * b) / gcd(a, b);
}