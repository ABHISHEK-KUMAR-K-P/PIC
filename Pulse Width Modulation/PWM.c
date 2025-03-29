#include <xc.h>
#define _XTAL_FREQ 20000000

// CONFIG
#pragma config FOSC = EXTRC        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

void SetPWMDutyCycle1(unsigned int DutyCycle)    // Give a value in between 0 and 1024 for DutyCycle
{
	CCPR1L   = DutyCycle>>2;        	        // Put MSB 8 bits in CCPR1L
	CCP1CON  = CCP1CON & 0xCF;                	// Make bit4 and 5 zero
	CCP1CON  = CCP1CON | (0x30&(DutyCycle<<4)); // Assign Last 2 LSBs to CCP1CON
}
   unsigned int i=0;

int main()
{
    TRISC = 0x00;                            // Make CCP1 pin as output
	  CCP1CON = 0x0C;                           // Configure CCP1 module in PWM mode
	  PR2 = 0xFF;                             // Configure the Timer2 period
	  T2CON = 0x04;   

 
	while(1)
	{
        //LED fade in
        for(i=0;i<1023;i++)
        {
          SetPWMDutyCycle1(i);   
          __delay_ms(8);
        }
         //LED fade out
         for(i=1023;i>0;i--)
        {
          SetPWMDutyCycle1(i);   
             __delay_ms(8);
        }
    }
    
    return 0;
     
}
