/***********************************************************************
 * 
 * Stopwatch with LCD display output.
 * ATmega328P (Arduino Uno), 16 MHz, AVR 8-bit Toolchain 3.6.2
 *
 * Copyright (c) 2017-2020 Tomas Fryza
 * Dept. of Radio Electronics, Brno University of Technology, Czechia
 * This work is licensed under the terms of the MIT license.
 * 
 **********************************************************************/

/* Includes ----------------------------------------------------------*/
#include <avr/io.h>         // AVR device-specific IO definitions
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC
#include "timer.h"          // Timer library for AVR-GCC
#include "lcd.h"            // Peter Fleury's LCD library
#include <stdlib.h>         // C library. Needed for conversion function

/* Variables ---------------------------------------------------------*/
// Custom character definition using https://omerk.github.io/lcdchargen/
uint8_t customChar[8] = {
	0b11111,
	0b00100,
	0b00100,
	0b11011,
	0b00100,
	0b00100,
	0b11111
	/*
	0b00000,
	0b11011,
	0b11011, // tohle je když chci další symbol ... prostì to napíšu za sebe a lcd_command si s tím poradí ( viz. lcd_command níže)
	0b00100,
	0b11011,
	0b11011,
	0b00000 */
};

/* Function definitions ----------------------------------------------*/
/**
 * Main function where the program execution begins. Update stopwatch
 * value on LCD display when 8-bit Timer/Counter2 overflows.
 */

int main(void)
{
    // Initialize LCD display
    lcd_init(LCD_DISP_ON);
	
	// Set pointer to beginning of CGRAM memory
	lcd_command(1 << LCD_CGRAM);
	for (uint8_t i = 0; i < 8; i++) // pro zapisování více symbolù tady akorát tøepíšu i < 8 na i < 16 a píšu dál ... pointer se automaticky posouvá po 8 øádcích na zaèátek dalšího symbolu
	{
		// Store all new chars to memory line by line
		lcd_data(customChar[i]);
	}
	// Set DDRAM address
	lcd_command(1 << LCD_DDRAM);
	
	// Display first custom character
	lcd_putc(0);

    // Put string(s) at LCD display
    lcd_gotoxy(1, 0);
    lcd_puts("00:00.0");
	lcd_gotoxy(11, 0);
    lcd_putc('a');
	lcd_gotoxy(1, 1);
	lcd_putc('b');
	lcd_gotoxy(11, 1);
	lcd_putc('c');

    // Configure 8-bit Timer/Counter2 for Stopwatch
    // Set prescaler and enable overflow interrupt every 16 ms
	TIM2_overflow_16ms();
	TIM2_overflow_interrupt_enable();

    // Enables interrupts by setting the global interrupt mask
    sei();

    // Infinite loop
    while (1)
    {
        /* Empty loop. All subsequent operations are performed exclusively 
         * inside interrupt service routines ISRs */
    }

    // Will never reach this
    return 0;
}

/* Interrupt service routines ----------------------------------------*/
/**
 * ISR starts when Timer/Counter2 overflows. Update the stopwatch on
 * LCD display every sixth overflow, ie approximately every 100 ms
 * (6 x 16 ms = 100 ms).
 */
ISR(TIMER2_OVF_vect)
{
    static uint8_t number_of_overflows = 0;
	static uint8_t tenths = 0;        // Tenths of a second
	static uint8_t secs = 0;        // Seconds
	static uint8_t tens = 0;		// tens of seconds
	static uint8_t a_sq = 0;
	static uint8_t minutes = 0;
	char lcd_string[2] = "  ";      // String for converting numbers by itoa()
	
	a_sq = secs * secs;
	itoa(a_sq, lcd_string, 10); // pøevod z 0 jako èísla na 0 jako string
	lcd_gotoxy(11, 0);
	lcd_puts(lcd_string);
	
    number_of_overflows++;
    if (number_of_overflows >= 6)
    {
        // Do this every 6 x 16 ms = 100 ms
        number_of_overflows = 0;

		tenths++;
		if(tenths > 1)
		{
			tenths = 0;
			secs++;
			if(secs > 9)
			{
				secs = 0;
				a_sq = 0;
				tens++;
				if(tens > 5)
				{
					tens = 0;
					minutes++;
					itoa(minutes, lcd_string, 10); // pøevod z 0 jako èísla na 0 jako string
					lcd_gotoxy(2, 0);
					lcd_puts(lcd_string);
				}
				itoa(tens, lcd_string, 10); // pøevod z 0 jako èísla na 0 jako string
				lcd_gotoxy(4, 0);
				lcd_puts(lcd_string);
			}
			itoa(secs, lcd_string, 10); // pøevod z 0 jako èísla na 0 jako string
			lcd_gotoxy(5, 0);
			lcd_puts(lcd_string);
		}
		
		itoa(tenths, lcd_string, 10); // pøevod z 0 jako èísla na 0 jako string
		lcd_gotoxy(7, 0);
		lcd_puts(lcd_string);

    }
}