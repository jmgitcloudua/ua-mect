#include <detpic32.h>
#include "delay.c"
#include "configSample.c"
#include "send2displays.c"
#include "toBCD.c"

#define numSamples 8

volatile unsigned char voltage = 0; // Global variable

// Interrupt Handler
void _int_(27) isr_adc(void) // Replace VECTOR by the A/D vector
                             // number - see "PIC32 family data
                             // sheet" (pages 74-76)
{

    // Print ADC1BUF0 value - Hexadecimal (3 digits format)
    // Read conversion result (ADC1BUF0 value) and print it
    /*printInt(ADC1BUF0, 16 | 3 << 16);
    delay(100);
    putChar(' ');
    */

    // Get average sample
    int VAL_AD = 0;
    int i = 0;
    int *p = (int *)(&ADC1BUF0);
    for (i = 0; i < numSamples; i++)
    {
        int value = p[i * 4];
        VAL_AD += value;
    }
    VAL_AD /= numSamples;

    // Calculate voltage amplitude
    // Convert voltage amplitude to decimal. Assign it to "voltage"
    voltage = (VAL_AD * 33 + 511) / 1023;

    // Reset AD1IF flag
    IFS1bits.AD1IF = 0;
}
int main()
{
	TRISB = TRISB & 0x80FF; //configure RB14-RB8 as outputs
    LATB = LATB & 0x80FF;   //set initial values

    TRISD = TRISD & 0xFF9F; //configure RD6-RD5 as outputs
    LATD = LATD & 0xFF9F;   //set initial values
    // Configure all (digital I/O, analog input, A/D module)
    configSample();

    // Configure interrupt system

    // Step1 -configure priority of A/D interrupts
    IPC6bits.AD1IP = 2;

    //Step2 - clear A/D interrupt flag
    IFS1bits.AD1IF = 0;

    //Step3- enable A/D interrupts
    IEC1bits.AD1IE = 1;

    //Step4 - Global Interrupt Enable
    EnableInterrupts();

    // Start A/D conversion
    int i = 0;
    while (1)
    {
        

        if (i++ == 25)
        { // 250 ms (4 samples/second)
            // Start ADC conversion
            AD1CON1bits.ASAM = 1;

            i = 0;
        }
        

        // Send "VOLTAGE" variable to displays
        send2displays(toBCD(voltage), 1);
        delay(10); // 10 ms
    }

    return 0;
}
