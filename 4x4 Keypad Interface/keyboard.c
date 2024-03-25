// This code is a simple program for interfacing a 4x3 matrix keypad with an ATmega32 microcontroller and displaying the pressed key on an LCD.



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
char lcd_Buffer[20];                                        // Buffer array to store string for displaying on LCD


void main(void){
    unsigned char key;
    PORTC = 0x00;                                           // Initializing PORTC
    DDRC = 0xF0;                                            // Configuring bits 4-7 of PORTC as output for keypad row
    lcd_init(16);                                           // Initializing the LCD module with 16 characters
    while (1){
        key = scan_key();                                   // Scanning for pressed key
        if (key != 0xFF){
            lcd_clear();                                    // Clearing the LCD
            lcd_gotoxy(0,0);                                // Setting cursor to the first position
            sprintf(lcd_Buffer , "Key = %c" , key);         // Formatting the LCD display message
            lcd_puts(lcd_Buffer);                           // Displaying the message on the LCD
        }
    }
}

unsigned char scan_key(void){
    unsigned char i, data, num_key, temp;
    num_key = 0xFF;                                         // Initializing num_key to default value
    temp = 0x70;                                            // Initial value for temp
    for (i = 0; i < 4; i++) {
        PORTC = temp;
        delay_ms(5);                                        // Delay for stability
        data = PINC & 0x0F;                                 // Reading the input data
        if (data == 0x07) { num_key = code[0][i]; }         // Checking for the pressed key in the first row
        if (data == 0x0B) { num_key = code[1][i]; }         // Checking for the pressed key in the second row
        if (data == 0x0D) { num_key = code[2][i]; }         // Checking for the pressed key in the third row
        if (data == 0x0E) { num_key = code[3][i]; }         // Checking for the pressed key in the fourth row
        temp = ((temp >>= 1) | 0x80) & 0xF0;                // Updating temp for the next row
    }
    return num_key;
}