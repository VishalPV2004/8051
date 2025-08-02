#include <reg51.h>

void delay();

void main() {
    unsigned char A = 0;
    P2 = 0x00;
    TMOD = 0x10;  // Timer1 in Mode 1 (16-bit timer)

    while (1) {
        // Rising loop
        for (A = 0; A != 0xFF; A++) {
            P2 = A;
            delay();
        }

        // Falling loop
        for (; A != 0x00; A--) {
            P2 = A;
            delay();
        }
    }
}

void delay() {
    TH1 = 0xF8;   // Load Timer1 high byte
    TL1 = 0xF8;   // Load Timer1 low byte
    TF1 = 0;      // Clear overflow flag
    TR1 = 1;      // Start Timer1

    while (TF1 == 0);  // Wait for overflow

    TR1 = 0;      // Stop Timer1
}
