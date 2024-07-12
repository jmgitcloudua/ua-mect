#include <stdio.h>
#include <string.h>

void printArray(char [], int [] , int);
void  cumSum(int [] , int [] , int );
int main(void){

        int a[] = {31,28,31,30,31,30,31,31,30,31,30,31};
        printArray("a", a, sizeof(a)/sizeof(*a));
        int b[12];
        cumSum(a, b,12);
        printArray("b", b,sizeof(a)/sizeof(*a));

        return 0;

}
void printArray(char s[12], int a[], int n) {
        printf("%s: \n ",s);
        int i;
    for (i = 0; i < n; i++) {
        printf(" %d ",a[i]);
    }
        printf("\n");
}

 void  cumSum(int a[], int b[], int n) {
    int c = 0;
    int i;
    for (i = 0; i < n; i++) {
        c += a[i];
        b[i] = c;
    }
}
//sizeof (C) / sizeof (C[0]) para calcular o tamanho de um array