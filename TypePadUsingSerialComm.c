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
#define dat P1

void main()
{
    unsigned char i = 0;
    unsigned char cursor_pos = 0x80;  // Start at 1st line, 1st position

    lcd_init();
    TMOD = 0x20;    // Timer1 in mode 2 (8-bit auto-reload)
    TH1 = 0xFD;     // Baud rate 9600 for 11.0592 MHz crystal
    SCON = 0x50;    // Serial mode 1, REN enabled
    TR1 = 1;

    lcd_cmd(cursor_pos);  // Set initial cursor position

    while(1)
    {
        while(RI == 0);   // Wait for serial input
        RI = 0;           // Clear receive flag

        if (SBUF == 8)  // ASCII backspace
        {
					
            if (cursor_pos == 0xC0)         // Beginning of second line
                cursor_pos = 0x8F;          // Move to end of first line
            else if (cursor_pos == 0x80)    // Beginning of first line
                cursor_pos = 0x80;          // Stay in place
            else
                cursor_pos--;               // Move one char back
						
						lcd_cmd(cursor_pos);
						lcd_data(' ');
            lcd_cmd(cursor_pos);            // Move cursor back again
        }
        else
        {
            lcd_data(SBUF);
            cursor_pos++;

            if (cursor_pos == 0x90)         // If end of first line
                cursor_pos = 0xC0;          // Go to second line
            else if (cursor_pos == 0xD0)    // If end of second line
                cursor_pos = 0xD0;          // Prevent overflow

            lcd_cmd(cursor_pos);            // Move cursor
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
    lcd_cmd(0x80);  // Cursor to beginning
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
