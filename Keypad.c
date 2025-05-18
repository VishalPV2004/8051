#include <reg51.h>

void delay(unsigned int ms);
void lcd_cmd(unsigned char s);
void lcd_data(unsigned char s);
void lcd_str(unsigned char *s);
void lcd_init();
char keypad();

sbit rs = P2^0;
sbit en = P2^1;
#define dat P3

sbit c1 = P1^0;
sbit c2 = P1^1;
sbit c3 = P1^2;

sbit r1 = P1^3;
sbit r2 = P1^4;
sbit r3 = P1^5;
sbit r4 = P1^6;

void main()
{
	P1 = 0xF8;  // Set C1-C3 as output (0), R1-R4 as input (1)
	lcd_init();
	lcd_cmd(0x80);
	lcd_str("Enter a number");
	delay(1000);
	lcd_cmd(0xC0); // cursor start at 2nd line

	while(1)
	{
		char key = keypad();
		if (key != 0)
			lcd_data(key);
	}
}

char keypad()
{
	char key = 0;
	while(1)
	{
		// Column 1
		c1 = 0; c2 = 1; c3 = 1;
		if(r1 == 0) { delay(20); while(r1==0); key = '3'; break; }
		if(r2 == 0) { delay(20); while(r2==0); key = '6'; break; }
		if(r3 == 0) { delay(20); while(r3==0); key = '9'; break; }
		if(r4 == 0) { delay(20); while(r4==0); key = '#'; break; }

		// Column 2
		c1 = 1; c2 = 0; c3 = 1;
		if(r1 == 0) { delay(20); while(r1==0); key = '2'; break; }
		if(r2 == 0) { delay(20); while(r2==0); key = '5'; break; }
		if(r3 == 0) { delay(20); while(r3==0); key = '8'; break; }
		if(r4 == 0) { delay(20); while(r4==0); key = '0'; break; }

		// Column 3
		c1 = 1; c2 = 1; c3 = 0;
		if(r1 == 0) { delay(20); while(r1==0); key = '1'; break; }
		if(r2 == 0) { delay(20); while(r2==0); key = '4'; break; }
		if(r3 == 0) { delay(20); while(r3==0); key = '7'; break; }
		if(r4 == 0) { delay(20); while(r4==0); key = '*'; break; }
	}
	return key;
}

void delay(unsigned int ms)
{
	unsigned int i, j;
	for(i = 0; i < ms; i++)
		for(j = 0; j < 1275; j++);
}

void lcd_init()
{
	lcd_cmd(0x38);
	lcd_cmd(0x0C);
	lcd_cmd(0x01);
	lcd_cmd(0x06);
	lcd_cmd(0x80);
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

