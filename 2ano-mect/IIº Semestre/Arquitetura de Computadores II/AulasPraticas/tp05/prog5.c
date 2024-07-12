/*
# -----------------------------------
# 2º Ano-2ºSemestre | Abril 2021
# Arquitectura de Computadores II
# Jodionisio Muachifi, 97147, MIECT
*/

#include <detpic32.h>
#include "toBCD.c"
#include "send2displays.c"
#include "delay.c"


#define numSamples 4

int main(void)
{
    // Step 1  - Configure the A/D module and port RB4 as
    // analog input
    TRISBbits.TRISB4 = 1;  // Step 1A - RB4 digital output disconnected
    AD1PCFGbits.PCFG4 = 0; // Step 1B - RB4 configured as analog input (AN4)

    AD1CHSbits.CH0SA = 4; // Step 2  - Desired input analog channel (0 to 15)

    AD1CON2bits.SMPI = numSamples - 1; // Step 3  - 4 samples will be converted and stored
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

    while (1)
    {

        // Start conversion
        AD1CON1bits.ASAM = 1;

        // Wait while conversion not done (AD1IF == 0)
        while (IFS1bits.AD1IF == 0);
            

        int i = 0, j = 0;
        double v = 0;
        unsigned char c;
        if (i++ % 25 == 0)
        {

            // Read conversion result(ADC1BUF0 - FF value) and print it int VAL_AD = 0;
            int *p = (int *)(&ADC1BUF0);
            int VAL_AD = 0;

            for (j = 0; j < numSamples; j++)
            {
                int value = p[j * 4];
                VAL_AD += value;
                //printInt(value, 10 | 4 << 10);
                //putChar(' ');
            }

            // Get average sample - Calculate buffer average
            VAL_AD = VAL_AD / numSamples;
            printf("\nAverage Sample Value = %d \n", VAL_AD);

            // Get tension amplitude - Calculate voltage amplitude
            v = (VAL_AD * 33 + 511) / 1023;
            printf("V_Amp = %f\n\n", v);

            // Convert voltage amplitude to decimal
            c = toBCD((char)v);

            // Reset AD1IF
            IFS1bits.AD1IF = 0;
            i = 0;
        }

        // Send voltage value to displays
        send2displays(c,1);

        // Wait 10 ms (using the core timer) - 100Hz
        delay(10);
    }
    return 0;
}