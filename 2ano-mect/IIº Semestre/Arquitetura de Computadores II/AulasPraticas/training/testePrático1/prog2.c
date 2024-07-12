#include <detpic32.h>

void send2displays(unsigned char value)
{
    static const char display7Scodes[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x67, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
    static char displayFlag = 0;

    // Configure RB8 to RB15 as outputs
    TRISB = (TRISB & 0x00FF);

    // Configure RD5 and RD6 as outputs
    TRISDbits.TRISD5 = 0;
    TRISDbits.TRISD6 = 0;

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
void delay(unsigned int ms)
{
    for (; ms > 0; ms--)
    {
        resetCoreTimer();
        while (readCoreTimer() < PBCLK / 1000)
            ;
    }
}
int main(void)
{
    int aux;
    int keyboard = -1; // if not valid
    int i;
    while (1)
    {
        keyboard = inkey();
        if (aux != 0)
        {
            keyboard = aux;
            putChar(keyboard);

            if (keyboard >= '0' && keyboard <= '3')
            {
                keyboard = keyboard - '0';
            }
            else
            {
                for (i = 0; i < 100; i++)
                {
                    send2displays(0xFF);
                    delay(10); //10ms =  1 seconds
                }
                // reset displays, all will be off
                LATB = LATB & 0x80FF;
                keyboard = -1;
            }
        }
        if (keyboard >= 0)
        {
            send2displays(keyboard);
            delay(10); // 10ms = 1 seconds
        }
    }

    return 0;
}