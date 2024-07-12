/*
# -----------------------------------
# 2º Ano-2ºSemestre | Abril 2021
# Arquitectura de Computadores II
# Jodionisio Muachifi, 97147, MIECT
*/
#include <detpic32.h>
#include "delay.c"

int main(void)
{
    LATCbits.LATC14 = 0;   // The initial value should be set                               //  before configuring the port as output
    TRISCbits.TRISC14 = 0; // RC14 configured as output
    while (1)
    {
        delay(500); // half period = 0.5s
        LATCbits.LATC14 = !LATCbits.LATC14;
    }
    return 0;
}
