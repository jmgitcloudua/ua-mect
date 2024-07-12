/*
# -----------------------------------
# 2º Ano-2ºSemestre | Abril 2021
# Arquitectura de Computadores II
# Jodionisio Muachifi, 97147, MIECT
*/
//---Impleting 7 segment display on Port B(two segment) using getChar()
// from a to g (include uppercase)

#include <detpic32.h>
#include "delay.c"

int main(void)
{
    LATD = LATD & 0xFF9F; // The initial value should be set
    LATB = LATB & 0x00FF; // before configuring the port as output

    TRISD = TRISD & 0xFF9F; // RD5 and RD6 configured as output
    TRISB = TRISB & 0x00FF; // RB8 to RB15 configured as output

    LATDbits.LATD5 = 1; // input
    LATDbits.LATD6 = 0; // output

    while (1)
    {
        delay(500); // 1Khz=0.5s = 500ms
        char c = getChar();

        switch (c)
        {
        //o segmento A está ligado ao porto RB8.
        case 'a' | 'A':
            LATB = LATB & 0x00FF;
            LATBbits.LATB8 = 1;
            break;

        case 'b' | 'B':
            LATB = LATB & 0x00FF;
            LATBbits.LATB9 = 1;
            break;

        case 'c' | 'C':
            LATB = LATB & 0x00FF;
            LATBbits.LATB10 = 1;
            break;

        case 'd' | 'D':
            LATB = LATB & 0x00FF;
            LATBbits.LATB11 = 1;
            break;

        case 'e' | 'E':
            LATB = LATB & 0x00FF;
            LATBbits.LATB12 = 1;
            break;

        case 'f' | 'F':
            LATB = LATB & 0x00FF;
            LATBbits.LATB13 = 1;
            break;

        case 'g' | 'G':
            LATB = LATB & 0x00FF;
            LATBbits.LATB14 = 1;
            break;

        case '.':
            LATB = LATB & 0x00FF;
            LATBbits.LATB15 = 1;
            break;

        default:
            LATB = LATB & 0x00FF;
            break;
        }
       
    }
    return 0;
}