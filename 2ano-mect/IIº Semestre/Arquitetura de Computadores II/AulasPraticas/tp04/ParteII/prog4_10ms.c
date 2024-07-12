/*
# -----------------------------------
# 2º Ano-2ºSemestre | Abril 2021
# Arquitectura de Computadores II
# Jodionisio Muachifi, 97147, MIECT
*/
#include <detpic32.h>
#include "delay.c"

static char displayFlag;

void send2displays(unsigned char value)
{
    static const char display7Scodes[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x67, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};

    // Determine digits
    int digit_low = value & 0x0F; // should be char but pcompile gives a warning and I don't like warnings :P
    int digit_high = value >> 4;  // value >> 4 & 0x000F would be the same, obviously

    // Send digit_low to display low
    if (displayFlag == 0)
    {
        LATB = (LATB & 0x00FF) | (display7Scodes[digit_low] << 8);
        LATDbits.LATD5 = 1;
        LATDbits.LATD6 = 0;
    }

    // Send digit_high to display high
    else
    {
        LATB = (LATB & 0x00FF) | (display7Scodes[digit_high] << 8);
        LATDbits.LATD5 = 0;
        LATDbits.LATD6 = 1;
    }

    // Toggle displayFlag
    displayFlag = !displayFlag;
}
int main(int argc, char const *argv[])
{
    // Configure RB8 to RB15 as outputs
    TRISB = (TRISB & 0x00FF);

    // RD5 to RD6 as outputs
    TRISD = TRISD & 0xFF9F;

    // Configure RB0 to RB3 as inputs
    TRISB = (TRISB & 0xFFF0) | 0x000F;

    unsigned int i = 0;
    unsigned char counter = 0;
    while (1)
    {
        i++;
        if (i % 20 == 0) //100Hz/5Hz=20
        {
            counter++;
        }
          // Send to display
        send2displays(counter);
        delay(10); // wait 10ms(100Hz)
    }
    return 0;
}
