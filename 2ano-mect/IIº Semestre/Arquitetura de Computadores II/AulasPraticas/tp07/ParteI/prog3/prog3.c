/**
 * Nome Jodionisio da Lucinda João Muachifi
 * Nº Mec: 97147
 * Cadeira de : Arquitetura de Computadores 2 | 2º Ano-2º semestre
 * Curso: MIECT  
 * Maio 2021
 */
#include <detpic32.h>

static int count = 1;
void _int_(12) isr_T3(void)
{
    if (count == 2)                 //calling putChar at 1Hz frequency
    {
        putChar('.');
        count = 1;
    }
    else
    {
        count++;
    }
    IFS0bits.T3IF = 0;              //reset T3IF interrupt flag
}

int main()
{
    //configure Timer T3
    T3CONbits.TCKPS = 7; //Kprescaler = 256, FoutPrescaler = 78125
    PR3 = 39062;         //Fout = 2Hz (PBLCK / (256*(39062+1))
    TMR3 = 0;            //reset timer T3 counter
    T3CONbits.TON = 1;   //enable timer T3

    //configure Timer T3 interrupts
    IPC3bits.T3IP = 2; //set priority
    IEC0bits.T3IE = 1; //enable interruputs
    IFS0bits.T3IF = 0; // reset interrupts flag
    EnableInterrupts();
    while (1);
        

    return 0;
}
