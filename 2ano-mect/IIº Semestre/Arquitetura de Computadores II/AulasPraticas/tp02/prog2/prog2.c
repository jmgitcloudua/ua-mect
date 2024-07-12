#include <detpic32.h>

void delay(int ms)
{
    for (; ms > 0; ms--)
    {
        resetCoreTimer();
        while (readCoreTimer() < 10000000); // k = 10000000 
        
    }
}
int main(void)
{
    int counter = 0;
    while (1)
    {
        delay(1000);// just for test
        printInt(++counter, 10 | 4 << 16); // Ver nota1      
        putChar('\r');            // cursor regressa ao início da linha
    }

    return 0;
}
