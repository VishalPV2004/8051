#include <reg51.h>

void delay(unsigned int ms);
void lcd_cmd(unsigned char s);
void lcd_data(unsigned char s);
void lcd_str(unsigned char *s);
void lcd_init();

sbit rs = P2^0;
sbit en = P2^1;
#define dat P3

void main()
{
	lcd_init();
	lcd_cmd(0x8f);      // Move cursor to last position of 1st line
	lcd_str("VeeConn");
	
	lcd_cmd(0x80);
	lcd_cmd(0x06);
	lcd_str("VeeConn");
	while(1);
}

void delay(unsigned int ms)
{
	unsigned int i, j;
	for(i = 0; i < ms; i++)
	{
		for(j = 0; j < 1275; j++);
	}
}

void lcd_init()
{
	lcd_cmd(0x38);  // 2 lines, 5x7 matrix
	lcd_cmd(0x0C);  // Display ON, cursor OFF
	lcd_cmd(0x01);  // Clear display
	lcd_cmd(0x80);  // Cursor to first line, first position
	lcd_cmd(0x04);  // Text to move from right to left
	//lcd_cmd(0x06)  left to right (default)
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
		lcd_data(*s);
		s++;
	}
}
