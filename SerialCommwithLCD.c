#include <reg51.h>

void delay(unsigned int ms);
void lcd_cmd(unsigned char s);
void lcd_data(unsigned char s);
void lcd_str(unsigned char *s);
void lcd_init();

sbit rs = P2^0;
sbit en = P2^1;
#define dat P1


void main()
{
    lcd_init();
    TMOD = 0x20;    // Timer1 in mode 2 (8-bit auto-reload)
    TH1 = 0xFD;     // Baud rate 9600 for 11.0592 MHz crystal
    SCON = 0x50;    // Serial mode 1, REN enabled
    TR1 = 1;

    while(1)
    {
        lcd_cmd(0x80);         // Start of first line
        lcd_str("Serial Data: ");

        while(RI == 0);        // Wait for data
        RI = 0;                // Clear receive interrupt
        if (SBUF >= 32 && SBUF <= 126)  // Printable ASCII check
        {
            lcd_cmd(0x8D);     // Print after "Serial Data: "
            lcd_data(SBUF);    // Display received character
        }

        delay(20);
    }
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
