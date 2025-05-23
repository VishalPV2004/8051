#include <reg51.h>

// \r\n+CMT: "+919999999999","","15/02/20,23:13:00+20"L1ON

void delay(unsigned int ms);
void lcd_cmd(unsigned char s);
void lcd_data(unsigned char s);
void lcd_str(unsigned char *s);
void lcd_init();
void sendser_str(unsigned char *s);
void sendser_char(unsigned char c);
void clear();
void I2C_start();
void I2C_stop();
void write_M2S(unsigned char);
unsigned char read_S2M();

sbit rs = P2^0;
sbit en = P2^1;
sbit SDA = P3^1;
sbit SCL = P3^0;
#define dat P1

unsigned char x;

void main() 
{
    lcd_init();
    TMOD = 0x20;
    TH1 = 0xFD;
    SCON = 0x50;
    IE = 0x90;
    TR1 = 1;

    lcd_cmd(0x80);
    lcd_str("VeeConn systems");
    delay(100);
    lcd_cmd(0x01);
    lcd_cmd(0x80);
    lcd_str("I2C Interface");
	
	  I2C_start();
	  write_M2S(0xA0);  // 7 bits of address + 1 bit read/write
	  write_M2S(0x00);  // Register address
	  write_M2S('V');	  
		I2C_stop();
	
	
	  delay(1000);
		
		I2C_start();
		write_M2S(0xA0);
		write_M2S(0x00);
		
		I2C_start();
		write_M2S(0xA1);
		x = read_S2M();
		I2C_stop();
		delay(50);
		
		lcd_cmd(0xC0);
		lcd_str("Data:");
		lcd_cmd(0xC6);
		lcd_data(x);
		

		while(1);
}

void write_M2S(unsigned char dta)
{
	 unsigned char i;
	 for(i = 0 ; i < 8 ; i++)
	  {
			SDA = (dta & 0x80) ? 1 : 0;
			SCL = 1;
			delay(5);
			SCL = 0;
			dta = dta << 1;
	  }
		
		SDA = 1;
		SCL = 1;
		delay(5);
		while(SDA == 1);   //Waiting for the Slave to pull SDA low as a sign of ACK
		
		SCL = 0;
		delay(5);
}

unsigned char read_S2M()
{
    bit rb_bit;
    unsigned char i, Dat = 0;

    for(i = 0 ; i < 8 ; i++)
    {
        Dat = Dat << 1;
        SCL = 1;
        delay(5);
        rb_bit = SDA;
        if(rb_bit) Dat |= 1;
        SCL = 0;
        delay(5);
    }

    // Master sends NACK
    SDA = 1;
    SCL = 1;
    delay(5);
    SCL = 0;

    return Dat;
}

void I2C_start()
{
	SCL = 1;
	SDA = 1;
	
	delay(5);
	SDA = 0;
	
	delay(5);
	SCL = 0;
}

void I2C_stop()
{
	SCL = 0;
	SDA = 0;
	
	delay(5);
	SCL = 1;
	
	delay(5);
	SDA = 1;
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
