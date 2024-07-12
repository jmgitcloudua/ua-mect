/*
# -----------------------------------
# 2º Ano-2ºSemestre | Abril 2021
# Arquitectura de Computadores II
# Jodionisio Muachifi, 97147, MIECT
*/
#include <detpic32.h>
#include "delay.c"

void send2displays(unsigned char value)
{
    static const char display7Scodes[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x67, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
    static char displayFlag = 0;
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
//--end send2Dispplay

unsigned char toBcd(unsigned char value)
{
    return ((value / 10) << 4) + (value % 10);
}
//--end toBcd
int main(int argc, char const *argv[])
{
    unsigned char counter = 0;
    unsigned int i = 0;
    while (1)
    {
        do
        {
            // call send2displays with counter value as argument
            send2displays(toBcd(counter));
            delay(10);      // wait 10ms(100Hz)
        } while (++i < 20); //100Hz/5Hz=20
        // increment counter (module 60)
        counter++;
        counter = counter % 60;

        return 0;
    }
