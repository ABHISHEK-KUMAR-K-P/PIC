
// PIC16F877A Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC = EXTRC     // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#define _XTAL_FREQ 20000000


void main(void) {
    TRISB=0x81; //setting RB0 and RB7 as inputs
    TRISD=0xFC; //setting RD0 and RD1 as outputs
    PORTB=0x00;
    while(1){
        if(PORTBbits.RB0==1){
            PORTDbits.RD0=1;
        }
        else if(PORTBbits.RB7==1){
            PORTDbits.RD1=1;
        }
        else{
            PORTDbits.RD0=0;
            PORTDbits.RD1=0;
        }
    }
    return;
}
