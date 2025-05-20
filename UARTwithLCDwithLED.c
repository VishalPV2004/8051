#include <reg51.h>

sbit rs = P2^0;
sbit en = P2^1;
sbit led = P2^6;
sbit input = P2^2;

#define dat P1

void delay(unsigned int ms);
void lcd_cmd(unsigned char);
void lcd_data(unsigned char);
void lcd_str(unsigned char *);
void lcd_init();
void uart_init();
void uart_send_str(unsigned char *s);

unsigned char *statusStr[] = {"OFF", "ON"};

void main()
{
	  P2 = 0x00;
    lcd_init();
    uart_init();
    lcd_cmd(0x80);
    lcd_str("LED Status: ");

    while(1)
    {
        unsigned char state;

        if (input == 1)
        {
            led = 1;         // Turn ON LED
            state = 1;
        }
        else
        {
            led = 0;         // Turn OFF LED
            state = 0;
        }

        lcd_cmd(0x8C);        // Position to print status
        lcd_str("   ");       // Clear old text
        lcd_cmd(0x8C);
        lcd_str(statusStr[state]);

        uart_send_str(statusStr[state]);
        uart_send_str("\r\n");

        delay(200);
    }
}

void delay(unsigned int ms)
{
    unsigned int i, j;
    for(i = 0; i < ms; i++)
        for(j = 0; j < 1275; j++);
}

void lcd_cmd(unsigned char s)
{
    rs = 0;
    dat = s;
    en = 1;
    delay(2);
    en = 0;
    delay(2);
}

void lcd_data(unsigned char s)
{
    rs = 1;
    dat = s;
    en = 1;
    delay(2);
    en = 0;
    delay(2);
}

void lcd_str(unsigned char *s)
{
    while(*s)
        lcd_data(*s++);
}

void lcd_init()
{
    lcd_cmd(0x38);
    lcd_cmd(0x0C);
    lcd_cmd(0x01);
    lcd_cmd(0x06);
    lcd_cmd(0x80);
}

void uart_init()
{
    TMOD = 0x20;      // Timer1, Mode2
    TH1 = 0xFD;       // 9600 baud rate for 11.0592 MHz
    SCON = 0x50;      // 8-bit, 1 stop bit, REN enabled
    TR1 = 1;
}

void uart_send_str(unsigned char *s)
{
    while(*s)
    {
        SBUF = *s++;
        while(TI == 0);
        TI = 0;
    }
}

