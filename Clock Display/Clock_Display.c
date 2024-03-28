// This code is essentially an Arduino sketch for an ATmega32 microcontroller that displays and increments time on an LCD screen.



#include <mega32.h>                                         // Including the necessary library for ATmega32 microcontroller
#include <stdio.h>                                          // Standard input-output library
#include <delay.h>                                          // Delay library for functions like delay_ms()
#asm
.equ __lcd_port=0x18;PORTB
#endasm
#include <lcd.h>
#include <string.h>
    

void main(void){
    int hour = 16;                                          // Initialize hour
    int minute = 15;                                        // Initialize minute
    int second = 33;                                        // Initialize second
    char zero[20] = "0";
    char str_hour[20];
    char str_minute[20];
    char str_second[20];

    PORTB = 0x00;                                           // Initialize PORTB
    DDRB = 0xFF;                                            // Set PORTB as output
    lcd_init(16);                                           // Initialize LCD
    lcd_clear();                                            // Clear LCD

    while (1){
        
        lcd_gotoxy(5,0);                                    // Display "Time:" on the LCD
        lcd_puts("Time:");
        delay_ms(100);
        lcd_gotoxy(3,1);                                    // Display hours, minutes, and seconds on the LCD
        lcd_puts(str_hour);
        lcd_puts(":");
        lcd_puts(str_minute);
        lcd_puts(":");
        lcd_puts(str_second);
        delay_ms(100);
        second++;                                           // Increment seconds and adjust minutes and hours accordingly
        if(second == 60) {
            second = 0;
            minute++;
            if(minute == 60) {
                minute = 0;
                hour++;
            }
        }
        sprintf(str_hour, "%d", hour);                      // Convert integers to strings for display
        sprintf(str_minute, "%d", minute);
        sprintf(str_second, "%d", second);

        if(hour < 10) {                                     // Add leading zeros if hour, minute, or second is less than 10
            strcat(zero, str_hour);
            strcpy(str_hour, zero);
            strcpy(zero, "0");
        }
        if(minute < 10) {
            strcat(zero, str_minute);
            strcpy(str_minute, zero);
            strcpy(zero, "0");
        }
        if(second < 10) {
            strcat(zero, str_second);
            strcpy(str_second, zero);
            strcpy(zero, "0");
        }
    }
}