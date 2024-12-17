#include <stdio.h>
#include <stdarg.h>

int add(int n, ...)
{
    va_list list;
    va_start(list, n); //initialize list to store arguments after n
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += va_arg(list, int); //get next argument
    }
    va_end(list); //clean up
    return sum;
}

int main()
{
    printf("1+2+3+4 = %d\n", add(4, 1, 2, 3, 4));
    printf("1+2+3+4+5 = %d\n", add(5, 1, 2, 3, 4, 5));
    printf("1+2+3+4+5+6 = %d\n", add(6, 1, 2, 3, 4, 5, 6));

    printf("--------------------\n");

    int a = 8;
    //a > 5 ? -1 : a++;
    printf("%d\n", a < 5 ? -1 : a++); //-1

    

    return 0;
}