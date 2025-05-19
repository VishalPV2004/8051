#include <reg51.h>

void delay(unsigned int ms);
void lcd_cmd(unsigned char s);
void lcd_data(unsigned char s);
void lcd_str(unsigned char *s);
void lcd_init();
unsigned char GetTemperatureAvg();
unsigned char GetTemperature();

sbit rs = P2^0;
sbit en = P2^1;
#define dat P3

sfr adc = 0x90;  // P1 as ADC data port
sbit cs = P2^2;
sbit rd = P2^3;
sbit wr = P2^4;
sbit intr = P2^5;

void main()
{
    unsigned char temp;
    lcd_init();

    while(1)
    {
        temp = GetTemperatureAvg();  // read ADC value
			  temp = (temp * 2) - 3;
        lcd_cmd(0x80);            // set LCD to 1st line
        lcd_str("Temp: ");
        lcd_data((temp/100)+'0');          // Hundreds
        lcd_data(((temp/10)%10)+'0');      // Tens
        lcd_data((temp%10)+'0');           // Units
        lcd_data(0xDF);                    // Degree symbol
        lcd_data('C');
        delay(500);
    }
}

unsigned char GetTemperatureAvg()
{
    unsigned int sum = 0;
    unsigned char i;
    for(i = 0; i < 5; i++) {
        sum += GetTemperature();
        delay(10);
    }
    return (unsigned char)(sum / 5);
}


unsigned char GetTemperature()
{
    unsigned char value;
    
    cs = 0;      // Enable ADC
    wr = 0;      // Start conversion
    delay(1);
    wr = 1;

    while(intr); // Wait till conversion complete

    rd = 0;      // Enable read
    value = adc;	// Read ADC value (P1 assumed connected)
    rd = 1;

    cs = 1;      // Disable ADC
    return value;
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
