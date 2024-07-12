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
    // Configure BaudRate Generator
    // Configure number of data bits (8), parity and number of stop bits
    // Enable the trasmitter and receiver modules
    // Enable UART2
    if (baud < 600 || baud > 115200)
    {
        baud = 115200;
    }
    if (parity != 'N' || parity != 'E' ||  parity != 'O')
    {
        parity = 'N';
    }
    if (stopbits != 1 || stopbits != 2)
    {
        stopbits = 1;
    }
    //UART2 configuration
    U2BRG = ((PBCLK + 8 * baud) / (16 * baud)) - 1; //constant U2BRG, baudrate = 115200 bps
    U2MODEbits.BRGH = 0;                                //16x baud clk enabled
    //Config parity, 8 bits
    switch (parity)
    {
    case 'N':
        U2MODEbits.PDSEL = 0; //8bits, no parity
        break;
    case 'E':
        U2MODEbits.PDSEL = 1; //8bits, even parity
        break;
    case 'O':
        U2MODEbits.PDSEL = 2; //8bits, odd parity
        break;
    }
    //Config stopbits
    switch (stopbits)
    {
    case 2:
        U2MODEbits.STSEL = 1; //2 stop bit
        break;
    case 1:
        U2MODEbits.STSEL = 0; //1 stop bit
        break;
    }
    U2STAbits.UTXEN = 1; //UART transmiter is enabled
    U2STAbits.URXEN = 1; //UART receiver is enabled
    U2MODEbits.ON = 1;   //UART enabled
}
void delay(int ms)
{
    for (; ms > 0; ms--)
    {
        resetCoreTimer();
        while (readCoreTimer() < 20000);
            
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
{   int TRMT_VAL;
    //configUart(600, 'N', 1);
    //configUart(1200, 'O', 2);
    //configUart(9600, 'E', 1);
    //configUart(19200, 'N', 2);
    configUart(115200, 'N', 2);
    TRISBbits.TRISB6 = 0; //config RB6 as output

    while (1)
    {
        resetCoreTimer();

         while(U2STAbits.TRMT == 1); 
        LATBbits.LATB6 = 1;   //set RB6
        //puts("12345");
        //puts("123456789");
        puts("123456789A");
        //puts("123456789AB");
        LATBbits.LATB6 = 0;   //reset RB6
        TRMT_VAL = readCoreTimer();
        printStr("\nTime: ");
        printInt10(TRMT_VAL*50);
        printStr("ns");
    }

    return 0;
}