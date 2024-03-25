// This code is a simple program for interfacing a 4x3 matrix keypad with an ATmega32 microcontroller and displaying the pressed key on an LCD.



#include <mega32.h>                                         // Including the necessary library for ATmega32 microcontroller
#include <stdio.h>                                          // Standard input-output library
#include <delay.h>                                          // Delay library for functions like delay_ms()
#asm
.equ __lcd_port = 0x1B;                                     // Assigning the address 0x1B to __lcd_port
#endasm
#include <lcd.h>

unsigned char scan_key(void);                               // Function prototype to scan keys on the keypad
char code[3][4] = {{'1', '4', '7', '*'},
                   {'3', '6', '9', '#'},
                   {'2', '0', '8', '5'}};
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

unsigned char scan_key(void) {
    unsigned char i, data, num_key, temp;
    num_key = 0xFF;                                         // Initialize num_key with an invalid value
    temp = 0x70;                                            // Set initial value for temp
    
    for (i = 0; i < 4; i++) {
        PORTC = temp;                                       // Set PORTC with the current value of temp
        delay_ms(5);                                        // Delay for stability       
        data = PINC & 0x0F;                                 // Read the lower 4 bits of PINC into the data variable
        
        // Check the value of data and assign the corresponding key from the code matrix
        if (data == 0x07)
            num_key = code[0][i];
        else if (data == 0x0B)
            num_key = code[1][i];
        else if (data == 0x0D)
            num_key = code[2][i];
        
        temp >>= 1;                                         // Shift temp one bit to the right to prepare for the next column scan
        temp |= 0x80;                                       // Set the most significant bit of temp to 1 to apply a high level to the next column
        temp &= 0xF0;                                       // Clear the 4 least significant bits of temp to ensure proper column scanning      
        delay_ms(5);                                        // Delay for stability
    }
    return num_key;
}