#include <reg51.h>

sbit led = P1^3;

void External_int1() interrupt 2 {
    led = 1; // LED ON when interrupt happens
    // Hardware clears EX1 automatically on ISR entry, no need to clear manually
	  led = 0;
}

void main() {
    P1 = 0x00;       // Set port 1 as output low

    IE = 0x84;       // EA=1, EX1=1, others 0: Enable external interrupt 1 and global interrupt

    TCON = 0x10;     // IT1=1 (edge triggered), IE1=0 (clear flag), EX1=0 (clear flag)
                     // 0x10 = 0001 0000 binary means IT1=1 (bit 4)

    led = 0;         // Start with LED OFF

}
