#include <detpic32.h>

int main(void){
    int counter = 0;
    while (1)
    {
        resetCoreTimer();
        while (readCoreTimer() < 10000000); // por a 10 000 000
        printInt(++counter, 10 | 4 << 16); // Ver nota 1      
        putChar('\r');            // cursor regressa ao início da linha    
        }   
    return 0;       
}