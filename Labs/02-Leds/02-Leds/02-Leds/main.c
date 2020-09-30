
#define LED_GREEN   PB5     // AVR pin where green LED is connected
#define LED_RED     PC0
#define BTN			PD0
#define BLINK_DELAY 250
#ifndef F_CPU
#define F_CPU 16000000      // CPU frequency in Hz required for delay
#endif

#include <util/delay.h>     // Functions for busy-wait delay loops
#include <avr/io.h>         // AVR device-specific IO definitions

int main(void)
{
    // Set pin as output in Data Direction Register...
    DDRB = DDRB | (1<<LED_GREEN);
    PORTB = PORTB & ~(1<<LED_GREEN);
	DDRC = DDRC | (1<<LED_RED);
	PORTC = PORTC & ~(1<<LED_RED);
	
	DDRD = DDRD & ~(1<<BTN); // tady mám nastavený pin s tlaèítkem jako vstupní
	PORTD = PORTD | (1<<BTN); // toto tu je kvùli tomu abych nemusel pøidìlávat externí pull-up resistor
	
    while (1)
    {
        _delay_ms(BLINK_DELAY);
		
		if (bit_is_clear(PIND, BTN))
		{		
			PORTB = PORTB ^ (1<<LED_GREEN);
			PORTC = PORTC ^ (1<<LED_RED);
		}
    }
    return 0;
}