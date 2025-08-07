#include<reg51.h>
#define dat P2

sbit rs = P3^0;
sbit en = P3^2;
void delay(unsigned int);
void lcd_cmd(unsigned char);
void lcd_data(unsigned char);
void lcd_init();
void lcd_clear();

int main()
{
	lcd_init();
	lcd_clear();
	lcd_cmd(0x14);
  //lcd_cmd(0x04);  // Set display shift ON before writing
	lcd_data('V');
	lcd_data('I');
	lcd_data('S');
	lcd_data('H');
	lcd_data('A');
	lcd_data('L');
	
	
	while (1)
    {
        lcd_cmd(0x18);  // Shift entire display left// Delay to control speed
    }
}


void lcd_clear()
{
	lcd_cmd(0x01);
	//lcd_cmd(0x8f);
	lcd_cmd(0x80);
}

void lcd_init()
{
	lcd_cmd(0x38);
	lcd_cmd(0x02);
	lcd_cmd(0x01);
	lcd_cmd(0x0E);
	lcd_cmd(0x80);
}

void lcd_data(unsigned char c)
{
	rs = 1;
	dat = c;
	en = 1;
	delay(5);
	en = 0;
	delay(5);
}

void delay(unsigned int x)
{
	unsigned int i,j;
	for(i = 0 ; i < x ; i++)
	{
		for(j = 0 ; j < 1275 ; j++)
		{
		}
	}
}

void lcd_cmd(unsigned char c)
{
	rs = 0;
	dat = c;
	en = 1;
	delay(5);
	en = 0;
	delay(5);
}
