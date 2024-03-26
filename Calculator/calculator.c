// This code is for implementing a simple calculator using an ATmega32 microcontroller and a keypad interfaced via PORTC.
// The calculator can perform basic arithmetic operations (+, -, *, /) on two numbers entered using the keypad.



#include <mega32.h>                                         // Including the necessary library for ATmega32 microcontroller
#include <stdio.h>                                          // Standard input-output library
#include <delay.h>                                          // Delay library for functions like delay_ms()
#asm
.equ __lcd_port = 0x1B;                                     // Assigning the address 0x1B to __lcd_port
#endasm
#include <lcd.h>

unsigned char scan_key(void);                               // Function prototype to scan keys on the keypad
char code[4][4] = {{'7', '4', '1', 'C'},{'8', '5', '2', '0'},
                   {'9', '6', '3', '='},{'/', '*', '-', '+'}};
char lcd_Buffer[20]; 

void main(void) {
    unsigned char key;
    int num1 = 0;
    int num2 = 0;
    char operator = '\0';
    PORTC = 0x00;
    DDRC = 0xF0;
    lcd_init(16);

    while (1) {
        key = scan_key();
        if (key != 0xFF) {
            lcd_clear();
            if (key >= '0' && key <= '9') {                         // Numeric keys
                if (operator == '\0') {
                    num1 = (num1 * 10) + (key - '0');
                    sprintf(lcd_Buffer, "Num1: %d", num1);
                } else {
                    num2 = (num2 * 10) + (key - '0');
                    sprintf(lcd_Buffer, "Num2: %d", num2);
                }
            } else if (key == '=' && operator != '\0') {             // Equals key
                int result;
                if (operator == '+') {
                    result = num1 + num2;
                } else if (operator == '-') {
                    result = num1 - num2;
                } else if (operator == '*') {
                    result = num1 * num2;
                } else if (operator == '/') {
                    result = (num2 != 0) ? num1 / num2 : 0;
                }

                sprintf(lcd_Buffer, "Result: %d", result);
            } else if (key == 'C') {                                 // Clear key
                num1 = 0;
                num2 = 0;
                operator = '\0';
                sprintf(lcd_Buffer, "Cleared");
            } else {                                                // Operator keys
                operator = key;
                sprintf(lcd_Buffer, "Operator: %c", operator);
            }

            lcd_gotoxy(0, 0);
            lcd_puts(lcd_Buffer);
        }
    }
}
unsigned char scan_key(void) {
    unsigned char i, data, num_key, temp;
    num_key = 0xFF;
    temp = 0x70;
    for (i = 0; i < 4; i++) {
        PORTC = temp;
        delay_ms(5);
        data = PINC & 0x0F;
        
        if (data == 0x07)
            num_key = code[0][i];  // Key 1, 4, 7, *
        if (data == 0x0B)
            num_key = code[1][i];  // Key 2, 5, 8, 0
        if (data == 0x0D)
            num_key = code[2][i];  // Key 3, 6, 9, #
        if (data == 0x0E)
            num_key = code[3][i];  // Key A, B, C, D
        
        temp = ((temp >>= 1) | 0x80) & 0xF0;
    }
    return num_key;
}