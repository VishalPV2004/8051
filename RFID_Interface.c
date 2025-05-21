#include <reg51.h>
#include <string.h>

void delay(unsigned int ms);
void lcd_cmd(unsigned char s);
void lcd_data(unsigned char s);
void lcd_str(unsigned char *s);
void lcd_init();
void serial_init();
void sendser_char(unsigned char s);
void sendser_str(unsigned char *s);
void clear(void);

sbit rs = P2^0;
sbit en = P2^1;
#define dat P1

unsigned char arr[11];
unsigned int i;
unsigned char set;

unsigned char tag1[11] = "10003B0CA7";
unsigned char tag2[11] = "10003B0CA7";


void serial_int(void) interrupt 4
{
	while(RI == 0);
	RI = 0;
	
	arr[i++] = SBUF;
	if (i == 10)
		set = 1;
}

void main()
{
	uart_send_str("UART TX working\n\r");
    lcd_init();
    serial_init();

    lcd_cmd(0x80);  // Set initial cursor position
	  lcd_str("VeeConn Systems");
	  delay(100);
	
	  lcd_cmd(0x01);
	  
	while(1)
	{
		  if (set == 0) 
			{
	        lcd_cmd(0x80);
	        lcd_str("Waiting for RFID tag");
		      delay(200);
		      lcd_cmd(0x01);
	    }
			
			if (set == 1)
			{
				 if (0 == strcmp(tag1,arr))
				 {
					 lcd_cmd(0x80);
					 lcd_str("Officer 1");
					 delay(400);
					 lcd_cmd(0x01);
					 clear();
					 sendser_str("Officer 1");
					 sendser_char(0x0d);
				 }
				 else if (0 == strcmp(tag2,arr))
				 {
		       lcd_cmd(0x80);
					 lcd_str("Officer 1");
					 delay(200);
					 lcd_cmd(0x01);
					 clear();
					 sendser_str("Officer 2");
					 sendser_char(0x0d);
				 }
				 else
				 {
					 lcd_cmd(0x80);
					 lcd_str("Invalid person!");
					 delay(200);
					 lcd_cmd(0x01);
					 clear();
					 sendser_str("Invalid Person!, activate security");
					 sendser_char(0x0d);
				 }
				 set = 0;
			}
			
  }
	 
}

void delay(unsigned int ms)
{
    unsigned int i, j;
    for(i = 0; i < ms; i++)
        for(j = 0; j < 1275; j++);
}

void clear()
{
	unsigned int j;
	for(j = 0 ; j < 100 ; j++)
	{
		arr[j] = '\0';
	}
}

void serial_init()
{
	  TMOD = 0x20;    // Timer1 in mode 2 (8-bt ato-reload)
    TH1 = 0xFD;     // Baud rate 9600 for 11.0592 MHz crystal
    SCON = 0x50;    // Serial mode 1, REN enabled
	  IE = 0x90;      // Enable serial interrup
    TR1 = 1;
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

void sendser_char(unsigned char c)
{
	SBUF = c;
	while(TI == 0);
	TI = 0;
}

void sendser_str(unsigned char *c)
{
	while(*c)
	{
		sendser_char(*c++);
		delay(2);
	}
}
