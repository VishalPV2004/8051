#include <reg51.h>

// \r\n+CMT: "+919999999999","","15/02/20,23:13:00+20"L1ON

void delay(unsigned int ms);
void lcd_cmd(unsigned char s);
void lcd_data(unsigned char s);
void lcd_str(unsigned char *s);
void lcd_init();
void sendser_str(unsigned char *s);
void sendser_char(unsigned char c);
void gsmLink();
void clear();
void send_sms();


sbit rs = P2^0;
sbit en = P2^1;
sbit l1 = P0^1;
#define dat P1

unsigned int display_msg_after_sending;
unsigned char a[100];
unsigned int i;
unsigned rx_flag;

void ser_int(void) interrupt 4
{
	if (RI == 1)
	{
		RI = 0;
		a[i] = SBUF;
		rx_flag = 1;
		i++;
	}
	
	if (TI == 1)
	{
		TI = 0;
	}
}

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
    lcd_str("GSM LINK Not OK");
    gsmLink();
    send_sms();

    while(1) {
        if (rx_flag == 1) {
            rx_flag = 0;

            delay(280);  //Wait till the array fills
            if (i >= 2 && a[0] == 'O' && a[1] == 'N') {
                clear();
                lcd_cmd(0x01);
                lcd_cmd(0x80);
                lcd_str(" BULB ON ");
                l1 = 1;
            }
            else if (i >= 3 && a[0] == 'O' && a[1] == 'F' && a[2] == 'F') {
                clear();
                lcd_cmd(0x01);
                lcd_cmd(0x80);
                lcd_str(" BULB OFF ");
                l1 = 0;
            }
            else {
                clear();
                lcd_cmd(0x01);
                lcd_cmd(0x80);
                lcd_str("Invalid data");
                delay(20);
            }
        }
        else {
            clear();
            lcd_cmd(0x01);
            lcd_cmd(0x80);
            lcd_str("Waiting..");
            delay(20);
        }
    }
}


void send_sms()
{
	lcd_cmd(0x01);
	lcd_cmd(0x80);
	lcd_str("Sending SMS : ");
	delay(650);
	
	sendser_str("AT+CMGS=");
	sendser_char(0x22);
	sendser_str("+919999999999");
	sendser_char(0x22);
	sendser_char(0x0D);
	delay(650);

	  sendser_str("VEECONN SYSTEMS");
	  sendser_char(0x1A);
	  
	  delay(5);
	  lcd_cmd(0x80);
	  lcd_cmd(0x01);
    delay(20);
	
		lcd_cmd(0x80);
	  lcd_str("SMS SENT");
		delay(20);
	  lcd_data(0x01);
	
    delay(50);
	
		lcd_cmd(0x80);
		lcd_str("VEECONN SYSTEMS");
		delay(20);
		clear();
		
		delay(6500);
		lcd_cmd(0x01);
}



void delay(unsigned int ms)
{
    unsigned int i, j;
    for(i = 0; i < ms; i++)
        for(j = 0; j < 1275; j++);
}

void gsmLink()
{
	loop:
	 i = 0;
	 sendser_str("AT");
	 sendser_char(0x0d);
	 lcd_cmd(0x80);
	 delay(2);
	
	if (a[0] == 'O' && a[1] == 'K')  //only due to proteus else 2 and 3rd indices
		lcd_str("GSM LINK Success!");
	else
	{
		lcd_str("GSM LINK Not ok!");
		goto loop;
	}
	clear();
	delay(650);

	loop1:
	 i = 0;
	 lcd_cmd(0x01);
	 sendser_str("AT+CMGF=1");
	 sendser_char(0x0d);
	 lcd_cmd(0x80);
	 delay(2);
	
	if (a[0] == 'O' && a[1] == 'K')
		lcd_str("GSM TEXT MODE");
	else
	{
		lcd_str("CONFIG TEXT..");
		goto loop1;
	}
	clear();
	delay(650);
}

void clear()
{
	unsigned int j = 0;
	for(j = 0 ; j < 100 ; j++)
	{
		a[j] = 0;
	}
	i = 0;
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
