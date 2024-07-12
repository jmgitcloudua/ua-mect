/**
 * Nome Jodionisio da Lucinda João Muachifi
 * Nº Mec: 97147
 * Cadeira de : Arquitetura de Computadores 2 | 2º Ano-2º semestre
 * Curso: MIECT  
 * Junho 2021
 */
#include <detpic32.h>

#define DisableUart2RxInterrupt() IEC1bits.U2RXIE = 0
#define EnableUart2RxInterrupt() IEC1bits.U2RXIE = 1
#define DisableUart2TxInterrupt() IEC1bits.U2TXIE = 0
#define EnableUart2TxInterrupt() IEC1bits.U2TXIE = 1

#define BUF_SIZE 8
#define INDEX_MASK (BUF_SIZE - 1)

#define FALSE 0
#define TRUE 1

typedef struct
{
    unsigned char data[BUF_SIZE]; //BUF_SIZE com o valor 8
    unsigned int head;
    unsigned int tail;
    unsigned int count;
} circularBuffer;

volatile circularBuffer txb; // Transmission buffer
volatile circularBuffer rxb; // Reception buffer

void comDrv_flushRx(void)
{
    // Initialize variables of the reception buffer
    rxb.head = 0;
    rxb.count = 0;
    rxb.tail = 0;
}
void comDrv_flushTx(void)
{
    // Initialize variables of the transmission buffer
    txb.head = 0;
    txb.count = 0;
    txb.tail = 0;
}

void comDrv_putc(char ch)
{
    while (txb.count == BUF_SIZE) // Wait while buffer is full
    {
    }
    txb.data[txb.tail] = ch;                // Copy character to the transmission
                                            // buffer at position "tail"
    txb.tail = (txb.tail + 1) & INDEX_MASK; // Increment "tail" index
                                            // (mod. BUF_SIZE)
    DisableUart2TxInterrupt();              // Begin of critical section
    txb.count++;                            // Increment "count" variable
    EnableUart2TxInterrupt();               // End of critical section
}

void comDrv_puts(char *s)
{
    while (*s != '\0')
    {
        comDrv_putc(*s);
        s++;
    }
}

char comDrv_getc(char *pchar)
{
    if (rxb.count == 0) // Test "count" variable (reception buffer) and return FALSE
    {
        return FALSE; // if it is zero
    }
    DisableUart2RxInterrupt();              // Begin of critical section
    *pchar = rxb.data[rxb.head];            // Copy character pointed by "head" to *pchar
    rxb.count--;                            // Decrement "count" variable
    rxb.head = (rxb.head + 1) & INDEX_MASK; // Increment "head" variable (mod BUF_SIZE)
    EnableUart2RxInterrupt();               // End of critical section
    return TRUE;
}

void _int_(32) isr_uart2(void)
{
    //Buffer TX
    if(IFS0bits.U1TXIF == 1){                       //Transmission interruption flag
        if(txb.count > 0){                          //means that there is info in the circular buffer
            U1TXREG =  txb.data[txb.head];          //copy char in head position to the U1TXREG register
            txb.head = (txb.head + 1) & INDEX_MASK; //increment "head" index (mod BUF_SIZE)
            txb.count--;
        }
        if(txb.count == 0){                    //means that there is no info in the circular buffer
            DisableUart1TxInterrupts();
        }
        IFS0bits.U1TXIF = 0;                        //reset UART1 TX interrupt flag   
    }
    //Buffer RX
    if(IFS0bits.U1RXIF == 1){                       //Reception interruption flag        
        rxb.data[rxb.tail] = U1RXREG;               //read a char from UART and write to the "tail" position
        rxb.tail = (rxb.tail + 1) & INDEX_MASK;     //increment "tail" index (mod BUF_SIZE)
        if(rxb.count < BUF_SIZE){                    //If buffer is not full
            rxb.count++;
        }else{
            rxb.head = (rxb.head + 1) & INDEX_MASK; //Increment "head" variable (discard oldest character)
        }
        IFS0bits.U1RXIF = 0;                        //reset UART1 RX interrupt flag
    }    
}

void comDrv_config(unsigned int baud, char parity, unsigned int stopbits)
{

    if (baud < 600 || baud > 115200)
    {
        baud = 115200;
    }
    if (parity != 'N' || parity != 'E' || parity != 'O')
    {
        parity = 'N';
    }
    if (stopbits != 1 || stopbits != 2)
    {
        stopbits = 1;
    }

    // Configure BaudRate Generator
    U2BRG = ((PBCLK + 8 * baud) / (16 * baud)) - 1;
    U2MODEbits.BRGH = 0; //16x baud clock enabled
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

    // Enable the trasmitter and receiver modules
    U2STAbits.UTXEN = 1; //UART2 transmiter is enabled
    U2STAbits.URXEN = 1; //UART2 receiver is enabled

    IPC8bits.U2IP = 2;   //priority 2
    IEC1bits.U2RXIE = 1; //interrupts enabled
    IEC1bits.U2TXIE = 1; //interrupts enabled

    IFS1bits.U2RXIF = 0; //reset Rx interrupt flag
    IFS1bits.U2TXIF = 0; //reset Tx interrupt flag

    // Enable UART2
    U2MODEbits.ON = 1; //UART2 enabled
}

int main(void)
{
    comDrv_config(115200, 'N', 1); // default "pterm" parameters
                                   // with TX and RX interrupts disabled
    comDrv_flushRx();
    comDrv_flushTx();
    EnableInterrupts();
    char s;
    comDrv_puts("PIC32 UART Device-driver\n");
    while (1)
        if (comDrv_getc(&s) == TRUE)
        {                   // Read character from reception buffer
            comDrv_putc(s); // Send character to the transmission buffer
        }
}
