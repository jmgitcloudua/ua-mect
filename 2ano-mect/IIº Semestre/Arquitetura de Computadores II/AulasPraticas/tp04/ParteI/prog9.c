/*
# -----------------------------------
# 2º Ano-2ºSemestre | Abril 2021
# Arquitectura de Computadores II
# Jodionisio Muachifi, 97147, MIECT
*/
#include <detpic32.h>


int main(int argc, char const *argv[])
{
    static const char display7Scodes[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x67, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};

    // Configure RB0 to RB3 as inputs
    TRISB = (TRISB & 0xFFF0) | 0x000F;

    // Configure RB8 to RB14 and RD5 to RD6 as outputs
    TRISB = (TRISB & 0x80FF);
    TRISD = TRISD & 0xFF9F;
    /*or
    TRISDbits.TRISD5 = 0;
    TRISDbits.TRISD6 = 0;
    */

    // Select display low
    LATDbits.LATD5 = 0;
    LATDbits.LATD6 = 1;

    while (1)
    {
        // Read dip-switch
        int value = PORTB & 0x000F;

        // Send to display
        LATB = (LATB & 0x80FF) | (display7Scodes[value] << 8);
    }

    return 0;
}
