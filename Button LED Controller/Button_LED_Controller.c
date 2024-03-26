// This code continuously checks the state of pin 0 on PORTC, and if it is high,
// it enters a loop that increments the value on PORTA from 1 to 15 while checking if pin 0 on PORTC remains high.
// If pin 0 on PORTC goes low during the loop, it resets PORTA to 0 and exits the loop. If pin 0 on PORTC is low initially, PORTA is set to 0 directly.
// The delay between each increment of PORTA is 100ms.



#include <mega32.h>
#include <delay.h>


// Declare your global variables here
int i=1;
void main(void){
    while (1){
        if(PINC.0 == 1){
            for(i=1; i<=15; i++){
                if(PINC.0 != 1){
                    PORTA = 0;
                    break;
                }
                PORTA = i;
                delay_ms(100);
            };
        }else{
            PORTA = 0;
        }
    }
}