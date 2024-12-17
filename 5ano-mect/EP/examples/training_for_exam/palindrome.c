// #include <stdio.h>

// int palindrome(int n, int reversed);

// int main()
// {
//     int n;
//     printf("Enter a positive integer: ");
//     if (scanf("%d", &n) != 1)
//     {
//         printf("Invalid input");
//         return 1;
//     }

//     if (palindrome(n, 0))
//         printf("%d is a palindrome number.\n", n);
//     else
//         printf("%d is not a palindrome number.\n", n);

//     return 0;
// }

// int palindrome(int n, int reversed)
// {
//     if (n == 0)
//     {
//         return (n == reversed);
//     }
//     else
//     {
//         return palindrome(n / 10, reversed * 10 + n % 10);
//     }
// }
#include <stdio.h>

int isPalindrome(int n);

int main()
{
    int n;
    printf("Enter a positive integer: ");

    if (scanf("%d", &n) != 1)
    {
        printf("Invalid input");
        return 1;
    }

    if (isPalindrome(n))
        printf("%d is a palindrome number.\n", n);
    else
        printf("%d is not a palindrome number.\n", n);

    return 0;
}

int isPalindrome(int n)
{
    int reversed = 0, original = n;

    while (n != 0)
    {
        int remainder = n % 10;
        reversed = reversed * 10 + remainder;
        n /= 10;
    }

    return original == reversed;
}
