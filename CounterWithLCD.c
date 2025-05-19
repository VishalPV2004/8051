#include <reg51.h>

void delay(unsigned int ms);
void lcd_cmd(unsigned char s);
void lcd_data(unsigned char s);
void lcd_str(unsigned char *s);
void lcd_init();
void GetCounterConfig();
void getNumbersOnLCD(unsigned char value);

sbit rs = P2^0;
sbit en = P2^1;
#define dat P1  // LCD data lines connected to Port 1

void main()
{
    lcd_init();
    lcd_cmd(0x80);
    lcd_str("VeeConn Systems");
    delay(100);

    lcd_cmd(0x01);    // clear screen
    delay(10);

    lcd_cmd(0x80);
    lcd_str("TH0 : ");
    lcd_cmd(0xC0);
    lcd_str("TL0 : ");

    GetCounterConfig();

    while(1);  // Infinite loop to hold display
}

void GetCounterConfig()
{
    unsigned char value;

    TMOD = 0x05;  // Timer 0 as Counter in Mode 1 (16-bit counter)
    TH0 = 0x00;   // Clear high byte
    TL0 = 0x00;   // Clear low byte
    TR0 = 1;      // Start counter

    delay(100);   // Wait while external pulses arrive on T0 (P3.4)

    while(1){
    // Display TH0
    value = TH0;
    lcd_cmd(0x86);           // Move to position after "TH0 : "
    getNumbersOnLCD(value);

    // Display TL0
    value = TL0;
    lcd_cmd(0xC6);           // Move to position after "TL0 : "
    getNumbersOnLCD(value);
		}
}

void getNumbersOnLCD(unsigned char value)
{
    lcd_data(value / 100 + '0');
    lcd_data((value / 10) % 10 + '0');
    lcd_data(value % 10 + '0');
}

void delay(unsigned int ms)
{
    unsigned int i, j;
    for(i = 0; i < ms; i++)
        for(j = 0; j < 1275; j++);
}

void lcd_init()
{
    lcd_cmd(0x38);  // 2 lines, 5x7 matrix
    lcd_cmd(0x0C);  // Display ON, cursor OFF
    lcd_cmd(0x01);  // Clear display
    lcd_cmd(0x06);  // Entry mode
    lcd_cmd(0x80);  // Force cursor to beginning
    delay(2);
}

void lcd_cmd(unsigned char s)
{
    rs = 0;
    dat = s;
    en = 1;
    delay(5);
    en = 0;
    delay(5);
}

void lcd_data(unsigned char s)
{
    rs = 1;
    dat = s;
    en = 1;
    delay(5);
    en = 0;
    delay(5);
}

void lcd_str(unsigned char *s)
{
    while(*s)
    {
        lcd_data(*s++);
    }
}
