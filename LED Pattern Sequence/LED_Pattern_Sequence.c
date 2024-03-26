// This code sequentially sets PORTD to specific binary values at different moments with a 100ms delay between each change,
// creating a pattern of LED states that resembles a visual effect.



#include <mega32.h>
#include <delay.h>


void main(void) {
    // Set the data direction register for PORTA as output
    DDRD = 0xFF;

    while (1) {
        // Moment 1
        PORTD = 0b10000001;
        delay_ms(100);

        // Moment 2
        PORTD = 0b01000010;
        delay_ms(100);

        // Moment 3
        PORTD = 0b00100100;
        delay_ms(100);

        // Moment 4
        PORTD = 0b00011000;
        delay_ms(100);

        // Moment 5
        PORTD = 0b00000000;
        delay_ms(100);

        // Moment 6
        PORTD = 0b00011000;
        delay_ms(100);

        // Moment 7
        PORTD = 0b00100100;
        delay_ms(100);

        // Moment 8
        PORTD = 0b01000010;
        delay_ms(100);

        // Moment 9
        PORTD = 0b10000001;
        delay_ms(100);
    }
}