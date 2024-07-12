/**
 * Nome Jodionisio da Lucinda João Muachifi
 * Nº Mec: 97147
 * Cadeira de : Arquitetura de Computadores 2 | 2º Ano-2º semestre
 * Curso: MIECT  
 * Junho 2021
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

void putc(char byte2send)
{
    while (U2STAbits.UTXBF == 1);
        
    //wait while UTXBF == 1
    U2TXREG = byte2send;
}
void puts(char *str)
{
    while (*str != '\0')
    {
        putc(*str);
        str++;
    }
}

int main(void)
{
    //UART2 configuration
    U2BRG = ((PBCLK + 8 * 115200) / (16 * 115200)) - 1; //constant U2BRG, baudrate = 115200 bps
    U2MODEbits.BRGH = 0;                                //16x baud clock enabled
    U2MODEbits.PDSEL = 0;                               //8bits, no parity
    U2MODEbits.STSEL = 1;                               //1 stop bit
    U2STAbits.UTXEN = 1;                                //UART transmiter is enabled
    U2STAbits.URXEN = 1;                                //UART receiver is enabled
    U2MODEbits.ON = 1;                                  //UART enabled

    while (1)
    {
        puts("String de teste\n");
        delay(1000); //wait 1 s
    }

    return 0;
}