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
#define dat P1

unsigned char lon[15] = {0};
unsigned char lat[15] = {0};
unsigned char arr[50] = {0};

unsigned char ch;
unsigned char start = 0;
unsigned int i = 0;
unsigned char done = 0;

void serial_int(void) interrupt 4
{
    ch = SBUF;
    RI = 0;

    if (ch == '$') {
        start = 1;
        i = 0;
    }

    if (start) {
        arr[i++] = ch;

        if (i >= sizeof(arr) - 1 || ch == '\n') {
            arr[i] = '\0'; // Null terminate
            start = 0;
            done = 1;
        }
    }
}

void main()
{
    unsigned int j, l = 0, p = 0;

    lcd_init();
    serial_init();
    lcd_cmd(0x80);  
    lcd_str("VeeConn Systems");
    delay(100);
    lcd_cmd(0x01);

    while (1)
    {
        if (!done) {
            lcd_cmd(0x80);
            lcd_str("Waiting...");
            delay(200);
            lcd_cmd(0x01);
        }
        else {
            if (arr[0] == 'G' && arr[1] == 'P' && arr[2] == 'G' && arr[3] == 'G' && arr[4] == 'A')
            {
                l = 0; p = 0;
                for (j = 0 ; j < 80 ; j++)
                {
                    if (j >= 18 && j <= 26)
                        lon[l++] = arr[j];
                    else if (j >= 30 && j <= 39)
                        lat[p++] = arr[j];
                }
                lon[l] = '\0';
                lat[p] = '\0';

                lcd_cmd(0x80);
                lcd_str("Lon: ");
                lcd_str(lon);
                lcd_cmd(0xC0);
                lcd_str("Lat: ");
                lcd_str(lat);

                delay(1000);
                lcd_cmd(0x01);
            }

            done = 0;
            clear();
        }
    }
}

void delay(unsigned int ms)
{
    unsigned int i, j;
    for (i = 0; i < ms; i++)
        for (j = 0; j < 1275; j++);
}

void clear()
{
    unsigned int j;
    for (j = 0; j < sizeof(arr); j++)
        arr[j] = '\0';
}

void serial_init()
{
    TMOD = 0x20;    // Timer1 mode2 (auto-reload)
    TH1 = 0xFD;     // Baud rate 9600 for 11.0592MHz
    SCON = 0x50;    // Mode 1, 8-bit UART
    IE = 0x90;      // Enable serial interrupt
    TR1 = 1;
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
    while (*s)
        lcd_data(*s++);
}


