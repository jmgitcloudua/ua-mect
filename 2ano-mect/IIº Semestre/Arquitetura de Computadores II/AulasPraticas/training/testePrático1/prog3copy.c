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

        /* if (decimalFlag == 1)
        { // Decimal point
            LATBbits.LATB15 = 1;
        }*/
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
int toBCD(unsigned char value)
{
    return ((value / 10) << 4) + (value % 10);
}
int main(void)
{
    // Step 1  - Configure the A/D module and port RB4 as
    // analog input
    TRISBbits.TRISB4 = 1;  // Step 1A - RB4 digital output disconnected
    AD1PCFGbits.PCFG4 = 0; // Step 1B - RB4 configured as analog input (AN4)

    AD1CHSbits.CH0SA = 4; // Step 2  - Desired input analog channel (0 to 15)

    AD1CON2bits.SMPI = 3; // Step 3  - 4 samples will be converted and stored
                          // in buffer locations ADC1BUF0 to ADC1BUF3

    AD1CON1bits.SSRC = 7; // Step 4  - Conversion trigger selection bits: in
                          // this mode an internal counter ends sampling and
                          // starts conversion

    AD1CON1bits.CLRASAM = 1; // Step 5 - Stop conversions when the 1st A/D
                             // converter interrupt is generated. At the same
                             // time, hardware clears the ASAM bit

    AD1CON3bits.SAMC = 16; // Step 6 - Sample time is 16 TAD (TAD = 100 ns)

    AD1CON1bits.ON = 1; // Step 7 (see Page 4) - Enable A/D converter
                        // This must the last command of the A/D
                        // configuration sequence

    int freq;
    int counter = 19; //contador Modulo 20
    int counterD = 0;
    int VAL_ADC = 0;
    int c = 0;
    int period = 50;
    while (1)
    {

        //start conversion
        AD1CON1bits.ASAM = 1;

        // Wait while conversion not done (AD1IF == 0)
        while (IFS1bits.AD1IF == 0)
            ;

        VAL_ADC = ADC1BUF0;
        freq = 1 + (VAL_ADC / 255);
        period = 50 / freq;
        if (++c >= period)
        {
            counter--; //down counter
            counterD = toBCD(counter);
            if (counter == 0)
            {
                counter = 19;
            }
            c = 0;
        }

        // Reset AD1IF
        IFS1bits.AD1IF = 0;
        
        send2displays(counterD);
        delay(20);
    }

    return 0;
}
