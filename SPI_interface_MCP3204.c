#include <reg51.h>

void delay(unsigned int ms);
void lcd_cmd(unsigned char s);
void lcd_data(unsigned char s);
void lcd_str(unsigned char *s);
void lcd_init();	
unsigned char spi_init();

unsigned char temp;
unsigned int i;

sbit rs = P2^1;
sbit en = P2^0;
#define dat P1
sbit clk=P3^0;
sbit din=P3^1;
sbit dout=P3^2;
sbit cs=P3^3;


void main()
{
    lcd_init();
	  lcd_cmd(0x01);
	  lcd_cmd(0x80);
	  lcd_str("VeeConn Systems");
	  
	  delay(200);
	  lcd_cmd(0xC0);
	  lcd_str("ADC value :");
	

    while(1)
    {
			lcd_cmd(0xC0);
			lcd_str("ADC value :");
			
			temp = spi_init();
			lcd_cmd(0xCC);
			temp = temp / 8.5;
      
		  lcd_data(temp/100 + '0');
			lcd_data((temp/10)%10 + '0');
			lcd_data(temp%10 + '0');
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

unsigned char spi_init()
{
	unsigned char temp = 0;
	char i;
	cs = 0;
	delay(5);
	clk = 0; din = 1; clk = 1;
	delay(5);
	clk = 0; din = 1; clk = 1;
	delay(5);
	
	clk = 0; din = 0; clk = 1;
	delay(5);
	clk = 0; din = 0; clk = 1;
	delay(5);
	clk = 0; din = 0; clk = 1;
	delay(5);
	clk = 0; din = 1; clk = 1;
	delay(5);
	clk = 0; din = 1; clk = 1;
	delay(5);
	for(i = 11 ; i >= 0 ; i--)
	{
		clk = 0;
		delay(2);
		if (dout == 1)
		{
			temp = temp | (1 << i);
		}
		delay(2);
		clk = 1;
	}
	delay(5);
	cs = 1;
	
	return temp;
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
