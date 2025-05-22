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


#include<xc.h>   
#define _XTAL_FREQ 20000000

unsigned char a;
void spi_write  (unsigned char value)
{
  SSPBUF = value;
  while(!SSPSTATbits.BF);
}
unsigned char spi_read()
{
  SSPBUF = 0x00;                // initiate bus cycle
  while(!PIR1bits.SSPIF);       // wait until cycle complete
  return (SSPBUF);              // return with byte read	
}
void write_EEPROM(unsigned char msb, unsigned char lsb, unsigned char data)
{
  PORTDbits.RD0 = 0;      // slave select low
  spi_write(0x06);
  PORTDbits.RD0 = 1;    // slave select high
  PORTDbits.RD0 = 0;    //slave select low
	spi_write(0x02);
	spi_write(msb);
	spi_write(lsb);
	spi_write(data);
  __delay_ms(500);
  PORTDbits.RD0 = 1;   //slave select high
  PORTDbits.RD0 = 0;   // slave select low
  spi_write(0x04);
  PORTDbits.RD0 = 1;  // slave select high

    	
}
void read_EEPROM(unsigned char msb, unsigned char lsb)
{
  PORTDbits.RD0 = 0; //slave select low
	spi_write(0x03);
	spi_write(msb);
	spi_write(lsb);
	while(!SSPSTATbits.BF );
	a = (spi_read());
  PORTDbits.RD0 = 1; //slave select high
}


int main()
{
  TRISCbits.TRISC3  = 0;        //   SERIAL CLOCK AS OUTPUT
  TRISCbits.TRISC4  = 1;       //  MISO AS INPUT
  TRISCbits.TRISC5  = 0;       // MOSI AS OUTPUT
  TRISDbits.TRISD0  = 0;       // SLAVE SELECT PIN D0 AS OUTPUT
  SSPCON = 0x20;
  SSPSTAT = 0x00;
  write_EEPROM(0x04,0x54,0x10);
  __delay_ms(1000);
  write_EEPROM(0x05,0x65,0x12);
  __delay_ms(1000);
  read_EEPROM(0x04,0x54);
  __delay_ms(1000);
  read_EEPROM(0x05,0x65);
  __delay_ms(1000);
  while(1)
  {
      //IDLE
  }
    return 0;
}
