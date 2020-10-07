/***********************************************************************
 * 
 * Alternately toggle two LEDs when a push button is pressed. Use 
 * functions from GPIO library.
 * ATmega328P (Arduino Uno), 16 MHz, AVR 8-bit Toolchain 3.6.2
 *
 * Copyright (c) 2019-2020 Tomas Fryza
 * Dept. of Radio Electronics, Brno University of Technology, Czechia
 * This work is licensed under the terms of the MIT license.
 * 
 **********************************************************************/

/* Defines -----------------------------------------------------------*/
#define LED_GREEN   PB5     // AVR pin where green LED is connected
#define LED_RED		PC0
#define BTN			PD0
#define BLINK_DELAY 500
#ifndef F_CPU
#define F_CPU 16000000      // CPU frequency in Hz required for delay
#endif

/* Includes ----------------------------------------------------------*/
#include <util/delay.h>     // Functions for busy-wait delay loops
#include <avr/io.h>         // AVR device-specific IO definitions
#include "gpio.h"           // GPIO library for AVR-GCC

/* Function definitions ----------------------------------------------*/
/**
 * Main function where the program execution begins. Toggle two LEDs 
 * when a push button is pressed. Functions from user-defined GPIO
 * library is used instead of low-level logic operations.
 */
int main(void)
{
	//1. ledka
    GPIO_config_output(&DDRB, LED_GREEN);
    GPIO_write_low(&PORTB, LED_GREEN);

	//2. ledka
	GPIO_config_output(&DDRC, LED_RED);
	GPIO_write_high(&PORTC, LED_RED);

	//Button
    GPIO_config_input_pullup(&DDRD,BTN);

    while (1)
    {
        _delay_ms(BLINK_DELAY);
		if(!GPIO_read(&PIND, BTN)) //GPIO_read pøeète z PIND pin BTN a pokud je 
		{
			GPIO_toggle(&PORTB, LED_GREEN); //&PORTB - & nám oznaèuje adresu toho portu
			GPIO_toggle(&PORTC, LED_RED);
		}

    }

    return 0;
}