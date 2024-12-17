#include <stdio.h>

#define g(x) (x + x)

int f(int x){
    return x + x;
}
int h(int x){
    return x++ ;
}
void i(){
    int (*a)[4];
    int b[10][4];
    a = b;
    b[0][0] = 20;
    b[1][0] = 40;
    printf("%p, %p\n", a, a + 1);
    printf("%d, %d\n", **a, **(a + 1));
}
// int j(int x, y++){
//     return x+y;
// }
int main(){

    int a[4] = {1, 2, 3, 4};
    printf("a[2] - a[1] =  %d\n", a[2] - a[1]);
    printf("&a[2]-&a[1] =  %ld\n", &a[2] - &a[1]);
    //printf("&a[2] =  %d\n", &a[2]);  
    //printf("&a[1] =  %d\n", &a[1]);
    //printf("&(a[2]-a[1]) = %d\n", &(a[2]-a[1]));

    int (*b)(char) = NULL;
    printf("b = %p\n", b);

    //  (1UL * 4)
    int c = 2UL * 4;
    int signed d = (int)(2UL * 4);
    printf("c = %d\n", c); // c = 4
    printf("d = %d\n", d); // d = 8

    printf("-------------\n");
    int x = 10;
    printf("g(x) = %d\n", g(x)); // g(x) = 20
    printf("f(x) = %d\n", f(x)); // f(x) = 20
    printf("f(x++) = %d\n", f(x++)); // f(x++) = 20
    x = 10;
    printf("f(++x) = %d\n", f(++x)); // f(++x) = 22
    x = 10;
    x = x + 1; //++x
    printf("g(++x) = %d\n", g(x)); // g(++x) = 22
    printf("g(x++) = %d\n", g(x)); // g(x++) = 22
    x = x + 1; //x++
    printf("-----------------\n");
    //int y = 3;
    //printf("%d %d\n", y, y++); // y++ is undefined behavior

    //call i()
    i();
    printf("-----------------\n");

    //call j()
    //printf("j(1, 2) = %d\n", j(1, 2)); // error: expected expression before ‘)’ token

    printf("-----------------\n");

    // I.1. The value of the expression (a > 5 ? -1 : a++) is:
    int a1 = 10;
    printf("I.1 = %d\n", (a1 > 5 ? -1 : a1++)); // -1
    //a1++;

    //I.3. If the variable x has value 3, then the expression (x + x++) has value:
    int x1 = 3;
    printf("I.3 = %d\n", (x1 + x1++)); // 6
    //x1++;

    //I.5. The expression h(x++) has value:
    int x2 = 3;
    printf("I.5 = %d\n", h(x2)); // 6

    //I.7. The expression (’a’ > 0) is:
    printf("I.7 = %d\n", ('a' > 0)); // 1
    
    //The value of expression (2 / 4 + 0.5) is:
    printf("I.8 = %f\n", 2 / 4 + 0.5); // 0.500000

    // I.9. The value of expression (0x1 + 5) is:
    printf("I.9 = %d\n", 0x1 + 5); // 6

    


    return 0;
}