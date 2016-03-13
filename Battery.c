/* Battery.c
 *  Author: martijus
 */ 

#define CPU_PRESCALE(n)	(CLKPR = 0x80, CLKPR = (n)) // Teensy Hz setting for UART
#define F_CPU 16000000L						// For _ms_delay function
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>		// For _ms_delay function
#include "uart.h"
#include "ADC.h"
#include "Timer.h"

// Battery Protection:
#define Batt_low	(PINF	|= (1<<PF1))	// Check if Pin F1 is high, then low battery detected.
#define Relay_on	(PORTB  |= (1<<PB1))	// Toggle Relay on.
#define Relay_off	(PORTB  &= ~(1<<PB1))	// Toggle Relay off.
#define isRelay_on	(PINB	|= (1<<PB1))	// Check if Pin B1 is high, then Relay is on (e.g. H&C is in cut-off)
#define isRelay_off	(PINB	&= ~(1<<PB1))	// Check if Pin B1 is low, then Relay is off (e.g. H&C is on)
#define LED_ON		(PORTD	|= (1<< PD6))	// Toggle Teensy LED on.
#define LED_OFF		(PORTD	&= ~(1<<PD6))	// Toggle Teensy LED off.

void isBatLow(void){
	if (PINF == Batt_low)			// Low battery level detected.
	{
		if (PINB == isRelay_off)	// Check to see if relay is already on
		{
			PORTB = Relay_on;		// When the relay turns on, the power to the heating & Cooling block is disconnected.
			//PORTD = LED_ON;		// for testing function
		}
	}
	
	if (PINF != Batt_low)		// Low battery level NOT detected.
	{
		PORTB = Relay_off;		// When there is no low battery detected the power to the heating & cooling block is connected.
		//PORTD = LED_OFF;		// for testing function
	}
}

void stopPCR(void){
	while (1)
	{
		PORTB = Relay_on;		// When there is no low battery detected the power to the heating & cooling block is connected.
		
		// For testing
		PIND = LED_ON;
		_delay_ms(1000);
		PIND = LED_OFF;
	}
}