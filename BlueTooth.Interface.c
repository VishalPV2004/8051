#include <reg51.h>
#include <string.h>

void delay(unsigned int ms);
void lcd_cmd(unsigned char s);
void lcd_data(unsigned char s);
void lcd_str(unsigned char *s);
void lcd_init(void);
void serial_init(void);
void clear(void);

sbit rs = P2^0;
sbit en = P2^1;
sbit fan = P2^2;
sbit lig = P2^3;
#define dat P1

unsigned char arr[6];  // 5 chars + 1 null terminator
unsigned int i = 0;
unsigned int flag = 0;

void serial_int(void) interrupt 4
{
    if(RI == 1)  // Check receive interrupt flag
    {
        RI = 0;
        arr[i++] = SBUF;
        if(i == 5)
        {
            arr[i] = '\0';  // Null terminate
            flag = 1;
            i = 0;
        }
    }
}

void main()
{
    lcd_init();
    serial_init();

    lcd_cmd(0x80);  
    lcd_str("VeeConn Systems");
    delay(100);
    lcd_cmd(0x01);
    lcd_cmd(0x80);
    lcd_str("Home automation");
    lcd_cmd(0xC0);
    lcd_str("Using ZigBee");
    delay(50);

    while(1)
    {
        if(flag == 1)
        {
            if(strcmp("L1ONN", arr) == 0)
            {
                lig = 1;
                lcd_cmd(0x01);
                lcd_cmd(0x81);
                lcd_str("Light 1 on");
                delay(300);
                lcd_cmd(0x01);
            }
            else if(strcmp("L1OFF", arr) == 0)
            {
                lig = 0;
                lcd_cmd(0x01);
                lcd_cmd(0x81);
                lcd_str("Light 1 off");
                delay(300);
                lcd_cmd(0x01);
            }
            else if(strcmp("F1ONN", arr) == 0)
            {
                fan = 1;
                lcd_cmd(0x01);
                lcd_cmd(0x81);
                lcd_str("Fan 1 on");
                delay(300);
                lcd_cmd(0x01);
            }
            else if(strcmp("F1OFF", arr) == 0)
            {
                fan = 0;
                lcd_cmd(0x01);
                lcd_cmd(0x81);
                lcd_str("Fan 1 off");
                delay(300);
                lcd_cmd(0x01);
            }
            else
            {
                lcd_cmd(0x01);
                lcd_cmd(0x81);
                lcd_str("Invalid data");
                delay(300);
                lcd_cmd(0x01);
            }

            flag = 0;   // Reset flag
            clear();    // Clear buffer for next data
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
    for(j = 0; j < sizeof(arr); j++)
        arr[j] = '\0';
}

void serial_init()
{
    TMOD = 0x20;    // Timer1 mode 2 auto reload
    TH1 = 0xFD;     // 9600 baud @ 11.0592 MHz
    SCON = 0x50;    // Serial mode 1, 8-bit UART, enable receiver
    IE = 0x90;      // Enable serial interrupt + global interrupt
    TR1 = 1;        // Start timer1
}

void lcd_init()
{
    lcd_cmd(0x38);  // 8-bit, 2 line, 5x7 dots
    lcd_cmd(0x0C);  // Display on, cursor off
    lcd_cmd(0x01);  // Clear display
    lcd_cmd(0x06);  // Entry mode: increment cursor
    lcd_cmd(0x80);  // Set cursor position to 1st line, 1st pos
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
        lcd_data(*s++);
}
