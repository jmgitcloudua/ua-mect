/*
# -----------------------------------
# 2º Ano-2ºSemestre | Abril 2021
# Arquitectura de Computadores II
# Jodionisio Muachifi, 97147, MIECT
*/
//---Impleting 4bits Binary up Counting with 4Hz of frequency

#include <detpic32.h>
#include "delay.c"


int main(void)
{   
    unsigned int counter = 0;
    LATE = LATE & 0xFFF0;   //  configured as output set all bit to zero                             //  before configuring the port as output
    TRISE = TRISE & 0xFFF0; // configured as output set all to zero
    while (1)
    {
        delay(250); // 0.25s = 250ms
        LATE = (LATE & 0xFFF0) | counter;
        counter++;
        //if(counter > 15) counter = 0;
        
    }
    return 1;
}
