

#define LED_GREEN1  PB1     // AVR pin where green LED is connected
#define LED_GREEN2  PB2
#define LED_GREEN3  PB3     // AVR pin where green LED is connected
#define LED_GREEN4  PB4
#define LED_GREEN5  PB5
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
	DDRB = DDRB | (1<<LED_GREEN1);
	PORTB = PORTB & ~(1<<LED_GREEN1);
	DDRB = DDRB | (1<<LED_GREEN2);
	PORTB = PORTB & ~(1<<LED_GREEN2);
	DDRB = DDRB | (1<<LED_GREEN3);
	PORTB = PORTB & ~(1<<LED_GREEN3);
	DDRB = DDRB | (1<<LED_GREEN4);
	PORTB = PORTB & ~(1<<LED_GREEN4);
	DDRB = DDRB | (1<<LED_GREEN5);
	PORTB = PORTB & ~(1<<LED_GREEN5);

	DDRD = DDRD & ~(1<<BTN); // tady mám nastavený pin s tlaèítkem jako vstupní
	PORTD = PORTD | (1<<BTN); // toto tu je kvùli tomu abych nemusel pøidìlávat externí pull-up resistor

	while (1)
	{

		if (bit_is_clear(PIND, BTN))
		{
			_delay_ms(BLINK_DELAY);
			PORTB = PORTB ^ (1<<LED_GREEN1);
			_delay_ms(BLINK_DELAY);
			PORTB = PORTB ^ (1<<LED_GREEN1);
			
			_delay_ms(BLINK_DELAY);
			PORTB = PORTB ^ (1<<LED_GREEN2);
			_delay_ms(BLINK_DELAY);
			PORTB = PORTB ^ (1<<LED_GREEN2);
			
			_delay_ms(BLINK_DELAY);
			PORTB = PORTB ^ (1<<LED_GREEN3);
			_delay_ms(BLINK_DELAY);
			PORTB = PORTB ^ (1<<LED_GREEN3);
			
			_delay_ms(BLINK_DELAY);
			PORTB = PORTB ^ (1<<LED_GREEN4);
			_delay_ms(BLINK_DELAY);
			PORTB = PORTB ^ (1<<LED_GREEN4);
			
			_delay_ms(BLINK_DELAY);
			PORTB = PORTB ^ (1<<LED_GREEN5);
			_delay_ms(BLINK_DELAY);
			PORTB = PORTB ^ (1<<LED_GREEN5);
			
			_delay_ms(BLINK_DELAY);
			PORTB = PORTB ^ (1<<LED_GREEN4);
			_delay_ms(BLINK_DELAY);
			PORTB = PORTB ^ (1<<LED_GREEN4);
			
			_delay_ms(BLINK_DELAY);
			PORTB = PORTB ^ (1<<LED_GREEN3);
			_delay_ms(BLINK_DELAY);
			PORTB = PORTB ^ (1<<LED_GREEN3);
			
			_delay_ms(BLINK_DELAY);
			PORTB = PORTB ^ (1<<LED_GREEN2);
			_delay_ms(BLINK_DELAY);
			PORTB = PORTB ^ (1<<LED_GREEN2);

}
	}
	return 0;
}
