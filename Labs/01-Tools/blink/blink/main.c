/***********************************************************************
 * 
 * Blink a LED and use the function from the delay library.
 * ATmega328P (Arduino Uno), 16 MHz, AVR 8-bit Toolchain 3.6.2
 *
 * Copyright (c) 2018-2020 Tomas Fryza
 * Dept. of Radio Electronics, Brno University of Technology, Czechia
 * This work is licensed under the terms of the MIT license.
 * 
 **********************************************************************/

/* Defines -----------------------------------------------------------*/
#define LED_GREEN   PB5     // AVR pin where green LED is connected (define pøejmenovává PB5 na LED_GREEN--vìtšinou na lepší pøehlednost kodu)
#define SHORT_DELAY 350      // Delay in miliseconds 
#ifndef F_CPU
#define F_CPU 16000000      // CPU frequency in Hz required for delay func
#endif

/* Includes ----------------------------------------------------------*/
#include <util/delay.h>     // Functions for busy-wait delay loops (#include pøidává knihovny)
#include <avr/io.h>         // AVR device-specific IO definitions

/* Variables ---------------------------------------------------------*/

/* Function prototypes -----------------------------------------------*/

/* Functions ---------------------------------------------------------*/
/**
 * Toggle one LED and use the function from the delay library.
 */
int main(void)
{
    // Set pin as output in Data Direction Register
    // DDRB = DDRB or 0010 0000 (DDRB = data direction register -- udává jestli bude vstupní nebo výstupní) (ledka PB5 bude v registru B proto ddrB a pin 5 -- výstupní pin má 1 a vstupní má 0)
    DDRB = DDRB | (1<<LED_GREEN); // (veznem DDBR v aktuálním stavu a | je funkce OR ) (<< je binární posunutí doleva TZN že 1 je v 8bit 00000001 a pøi posunutí o 5 pozic(PB5) to vypadá 00100000) (poté pøi fci OR mezi 00000000 a 00100000 nám zmìní hodnotu 5. pinu na 1 (tzn výstup))
    // Set pin LOW in Data Register (LED off) (kod aby ledka nesvítila na zaèátku)
    // PORTB = PORTB and 1101 1111
    PORTB = PORTB & ~(1<<PB5); //(& je logický souèin a ~ je negace)
    // Infinite loop
    while (1)
    {
        // Pause several miliseconds
        _delay_ms(SHORT_DELAY);

        // Invert LED in Data Register (když chceme ledkou blikat)
        // PORTB = PORTB xor 0010 0000
        PORTB = PORTB ^ (1<<LED_GREEN); // (^ je fce XOR)
		_delay_ms(SHORT_DELAY*3);
		PORTB = PORTB ^ (1<<LED_GREEN);
		_delay_ms(SHORT_DELAY);
		PORTB = PORTB ^ (1<<LED_GREEN);
		_delay_ms(SHORT_DELAY);
		PORTB = PORTB ^ (1<<LED_GREEN);
		_delay_ms(SHORT_DELAY);
		PORTB = PORTB ^ (1<<LED_GREEN);
		_delay_ms(SHORT_DELAY);
		PORTB = PORTB ^ (1<<LED_GREEN);
		_delay_ms(SHORT_DELAY*5); // D
		
		PORTB = PORTB ^ (1<<LED_GREEN);
		_delay_ms(SHORT_DELAY);
		PORTB = PORTB ^ (1<<LED_GREEN);
		_delay_ms(SHORT_DELAY*5); // E
		
		PORTB = PORTB ^ (1<<LED_GREEN);
		_delay_ms(SHORT_DELAY);
		PORTB = PORTB ^ (1<<LED_GREEN);
		_delay_ms(SHORT_DELAY);
		PORTB = PORTB ^ (1<<LED_GREEN);
		_delay_ms(SHORT_DELAY);
		PORTB = PORTB ^ (1<<LED_GREEN);
		_delay_ms(SHORT_DELAY);
		PORTB = PORTB ^ (1<<LED_GREEN);
		_delay_ms(SHORT_DELAY*3);
		PORTB = PORTB ^ (1<<LED_GREEN);
		_delay_ms(SHORT_DELAY);
		PORTB = PORTB ^ (1<<LED_GREEN);
		_delay_ms(SHORT_DELAY*3);
		PORTB = PORTB ^ (1<<LED_GREEN);
		_delay_ms(SHORT_DELAY);
		PORTB = PORTB ^ (1<<LED_GREEN);
		_delay_ms(SHORT_DELAY*3);
		PORTB = PORTB ^ (1<<LED_GREEN);
		_delay_ms(SHORT_DELAY*5);
    }

    // Will never reach this
    return 0;
}

/* Interrupt routines ------------------------------------------------*/


