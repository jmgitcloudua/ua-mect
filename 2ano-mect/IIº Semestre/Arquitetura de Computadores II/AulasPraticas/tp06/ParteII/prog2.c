#include <detpic32.h>
#include "delay.c"
#include "configSample.c"

volatile int adc_value; //global variable

// Interrupt Handler
void _int_(27) isr_adc(void) // Replace VECTOR by the A/D vector
                             // number - see "PIC32 family data
                             // sheet" (pages 74-76)
{
    //LATEbits.LATE0 = 0; // Reset RE0 - LATE0 = 0

    // Read ADC1BUF0 value to "adc_value"
    adc_value = ADC1BUF0;

   // LATEbits.LATE0 = 1; // Reset RE0 - LATE0 = 1

    // Print ADC1BUF0 value - Hexadecimal (3 digits format)
    // Read conversion result (ADC1BUF0 value) and print it
    /*printInt(ADC1BUF0, 16 | 3 << 16);
    delay(100);
    putChar(' ');
    */

    // Start conversion
    AD1CON1bits.ASAM = 1;

    // Reset AD1IF flag
    IFS1bits.AD1IF = 0;

    LATEbits.LATE0 = 1; // Reset RE0 - LATE0 = 1
}
int main()
{
    TRISEbits.TRISE0 = 0;
	
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
    AD1CON1bits.ASAM = 1;
    while (1)
    {
        LATEbits.LATE0 = 0; // Reset RE0 - LATE0 = 0
    } // all activity is done by the ISR

    return 0;
}
