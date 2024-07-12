/**
 * Nome Jodionisio da Lucinda João Muachifi
 * Nº Mec: 97147
 * Cadeira de : Arquitetura de Computadores 2 | 2º Ano-2º semestre
 * Curso: MIECT  
 * Maio 2021
 */
#include <detpic32.h>

int main(void)
{
    T3CONbits.TCKPS = 7; //Kprescaler = 256, FoutPrescaler = 78125
    PR3 = 39062;         //Fout = 2Hz (PBLCK / (256*(39062+1))
    TMR3 = 0;            //Reset timer T3 count register
    T3CONbits.TON = 1;   //Enable timer T3

    while (1)
    {
         //wait while T3IF == 0
        while (IFS0bits.T3IF == 0);
        
        //reset T3IF          
        IFS0bits.T3IF = 0; 
        putChar('.');
    }
    return 0;
}
