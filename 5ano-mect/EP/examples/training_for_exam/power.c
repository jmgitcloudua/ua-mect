#include <stdio.h>

int power(int base, int a);

int main()
{
    int base, a;
    printf("Enter base number: ");
    if(scanf("%d", &base) != 1)
    {
        printf("Invalid input");
        return 1;
    }
    printf("Enter power number(positive integer): ");
    if(scanf("%d", &a) != 1)
    {
        printf("Invalid input");
        return 1;
    }
    printf("%d^%d = %d \n", base, a, power(base, a));
    return 0;
}

// powe using recursion
int power(int base, int a)
{
    if (a != 0)
        return (base * power(base, a - 1));
    else
        return 1;

}