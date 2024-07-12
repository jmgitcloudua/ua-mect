/**
 * Nome Jodionisio da Lucinda João Muachifi
 * Nº Mec: 97147
 * Cadeira de : Arquitetura de Computadores 2 | 2º Ano-2º semestre
 * Curso: MIECT  
 * Junho 2021
 */
#include <detpic32.h>

void configUart(unsigned int baud, char parity, unsigned int stopbits)
{
    if (baud < 600 || baud > 115200)
        baud = 115200;
    if (parity != 'N' || parity != 'E' || parity != 'O')
        parity = 'N';
    if (stopbits != 1 || stopbits != 2)
        stopbits = 1;

    U2BRG = ((PBCLK + 8 * baud) / (16 * baud)) - 1; //configure baudrate generator
    U2MODEbits.BRGH = 0;                            //16x baud clk enabled

    //config parity,  nºbits = 8
    switch (parity)
    {
    case 'N':
        U2MODEbits.PDSEL = 0; //8 bits, no parity
        break;
    case 'E':
        U2MODEbits.PDSEL = 1; //8 bits, even parity
        break;
    case 'O':
        U2MODEbits.PDSEL = 2; //8 bits, odd parity
        break;
    }

    //config stopbits
    switch (stopbits)
    {
    case 2:
        U2MODEbits.STSEL = 1; //2 stop bits
        break;
    case 1:
        U2MODEbits.STSEL = 0; //1 stop bit
        break;
    }

    U2STAbits.URXEN = 1; //UART1 receiver is enabled
    U2STAbits.UTXEN = 1; //UART1 transmitter is enabled
    U2MODEbits.ON = 1;   //UART1 enabled
}

void putc(char byte2send)
{
    while (U2STAbits.UTXBF == 1);
    //wait while UTXBF==1
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
char getc(void) 
 { 
     if (U2STAbits.OERR == 1)
     {
         U2STAbits.OERR == 0;
     }
     while(U2STAbits.URXDA == 0);
     if (U2STAbits.FERR == 1 || U2STAbits.PERR == 1)
     {
         char a = U2RXREG;
         return 0;
     }
     else
     {
         return U2RXREG;
     }
      
 // If OERR == 1 then reset OERR 
 // Wait while URXDA == 0 
 // If FERR or PERR then 
 // read UxRXREG (to discard the character) and return 0 
 // else 
 // Return U2RXREG 
 }
int main(void)
{
    configUart(115200, 'N', 1); // default "pterm" parameters
    while (1)
    {
        putc(getc());
    }

    return 0;
}