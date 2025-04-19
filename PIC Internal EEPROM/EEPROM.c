/*
 * File:   INTEEPROM.c
 * Author: Abhishek Kumar 
 *
 * Created on 19 April, 2025, 10:40 AM
 */

#include <xc.h>
#define _XTAL_FREQ 20000000
// CONFIG
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF         // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#define RS PORTDbits.RD0
#define RW PORTDbits.RD1
#define EN PORTDbits.RD2

char byte;

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


void ReadByteFromEE(const unsigned char address)
{
    EEADR = address;       
 	  EECON1bits.EEPGD = 0;         
	  EECON1bits.RD = 1 ;       
	  byte = EEDATA;
}

void WriteByteToEE(unsigned char data, const unsigned char address)
{
         EEADR  = address; 
	       EEDATA = data;         
      	 EECON1bits.EEPGD = 0;
	   	   EECON1bits.WREN = 1;      
      	 EECON2 = 0x55;  
      	 EECON2 = 0xAA;
	       EECON1bits.WR = 1;   
         while(PIR2bits.EEIF==0);
         PIR2bits.EEIF = 0;
	   	   EECON1bits.WR = 0;         
         EECON1bits.WREN = 0;
          
}


void main(void) 
{
    TRISC = 0x00;
    TRISD = 0x00;
    lcd_initialise();
    
    WriteByteToEE(7, 0X0A);
    //ReadByteFromEE(0X0A);
    WriteByteToEE(8, 0X0B);
    //ReadByteFromEE(0X0B);
    
    while(1)
    {
        lcd_command(0x80); //Row 1 Column 1
        lcd_string("EEPROMVALUE OXOA",16);
        ReadByteFromEE(0X0A);
        lcd_command(0xC0); //Row 2 Column 1
        lcd_data(byte+0x30);
        __delay_ms(2000); //2 seconds delay
        lcd_command(0x01); //clear LCD
        lcd_command(0x80);
        lcd_string("EEPROMVALUE OXOB",16);
        ReadByteFromEE(0X0B);
        lcd_command(0xC0);
        lcd_data(byte+0x30);
        __delay_ms(2000);
        lcd_command(0x01);
    }
    return;
}

