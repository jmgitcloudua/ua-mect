/*
# -----------------------------------
# 2º Ano-2ºSemestre | Abril 2021
# Arquitectura de Computadores II
# Jodionisio Muachifi, 97147, MIECT
*/
#include <detpic32.h>

void delay(int ms)
{
    for (; ms > 0; ms--)
    {
        resetCoreTimer();
        while (readCoreTimer() < 20000)
            ;
    }
}
void sendSegment(unsigned char c)
{
    LATB = LATB & 0x00FF;
    switch (c)
    {
    //The segment A is switch on to RB8 Port
    case 'a':
        LATBbits.LATB8 = 1;
        break;

    case 'b':
        LATBbits.LATB9 = 1;
        break;

    case 'c':
        LATBbits.LATB10 = 1;
        break;

    case 'd':
        LATBbits.LATB11 = 1;
        break;

    case 'e':
        LATBbits.LATB12 = 1;
        break;

    case 'f':
        LATBbits.LATB13 = 1;
        break;

    case 'g':
        LATBbits.LATB14 = 1;
        break;

    default:
        break;
    }
}
int main(void)
{
    unsigned char segment;

    LATDbits.LATD6 = 1; // display high active
    LATDbits.LATD5 = 0; // display low inactive

    LATB = LATB & 0x00FF;
    TRISB = TRISB & 0x00FF;          // configure RB8-RB14 as outputs
    TRISD = TRISD & 0xFF9F;          // configure RD5-RD6 as outputs
    LATD = (LATD & 0xFF9F) | 0x0040; // display high active, low inactive
    while (1)
    {

        LATD = LATD ^ 0x0060; // toggle display selection
        segment = 'a';
        int i;
        for (i = 0; i < 7; i++)
        {
            sendSegment(segment); // send "segment" value to display
            delay(100);           // 10Hz=100ms, 50Hz=20ms, 100Hz=10ms
            segment++;            // segsegment = segment << 1;
        }
    }
    return 0;
}
