
// PIC16F877A Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC = EXTRC     // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#define _XTAL_FREQ 20000000 



#define RS PORTDbits.RD0
#define RW PORTDbits.RD1
#define EN PORTDbits.RD2

#define C1 PORTBbits.RB0
#define C2 PORTBbits.RB1
#define C3 PORTBbits.RB2
#define R1 PORTBbits.RB4
#define R2 PORTBbits.RB5
#define R3 PORTBbits.RB6
#define R4 PORTBbits.RB7

void lcd_data(unsigned char data)
{
    PORTC = data;
    RS = 1;
    RW = 0;
    EN = 1;
    __delay_ms(5);
    EN = 0;
}

void lcd_command(unsigned char cmd)
{
    PORTC = cmd;
    RS = 0;
    RW = 0;
    EN = 1;
    __delay_ms(5);
    EN = 0;
}

void lcd_string(const unsigned char *str,unsigned char num)  
{
    unsigned char i;
    for(i=0;i<num;i++)
    {
      lcd_data(str[i]);  
        
    }
}

void lcd_initialise()
{
    lcd_command(0x38);
    lcd_command(0x06);
    lcd_command(0x0C);
    lcd_command(0x01);
}

void keypad()
{
    C1=1;C2=0;C3=0;
    if(R1==1)
    {
        lcd_data('1');
        while(R1==1);
    }
    if(R2==1)
    {
        lcd_data('4');
        while(R2==1);
    }
    if(R3==1)
    {
        lcd_data('7');
        while(R3==1);
    }
    if(R4==1)
    {
        lcd_data('*');
        while(R4==1);
    }
    C1=0;C2=1;C3=0;
    if(R1==1)
    {
        lcd_data('2');
        while(R1==1);
    }
    if(R2==1)
    {
        lcd_data('5');
        while(R2==1);
    }
    if(R3==1)
    {
        lcd_data('8');
        while(R3==1);
    }
    if(R4==1)
    {
        lcd_data('0');
        while(R4==1);
    }
    C1=0;C2=0;C3=1;
    if(R1==1)
    {
        lcd_data('3');
        while(R1==1);
    }
    if(R2==1)
    {
        lcd_data('6');
        while(R2==1);
    }
    if(R3==1)
    {
        lcd_data('9');
        while(R3==1);
    }
    if(R4==1)
    {
        lcd_command(0x01);// # in Keypad will be used to clear the LCD screen
        while(R4==1);
    }
}


void main(void) 
{
    TRISC = 0x00;
    TRISD = 0x00;
    TRISB = 0xF0;
    lcd_initialise();
    lcd_command(0x80);
    lcd_string("WELCOME!",8);
    __delay_ms(1000);
    lcd_command(0x01);
    while(1)
    {
       keypad();
        
    }
    return;
}
