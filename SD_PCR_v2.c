/* SD_PCR.c
 *  Author: martijus
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>	
#include <util/delay.h>		// For _ms_delay function
#include "uart.h"			// Controls data transfer between the Bluetooth (App) and Teensy.
#include "ADC.h"			// Controls read thermistor values into the Teensy
#include "Timer.h"			// Controls PWM and ISR counter
#include "Battery.h"		// Controls battery cut-off 
#include "H_C.h"

/////////// Begin Definitions: ////////////////////////////////////////////
#define LED_ON		(PORTD	|= (1<< PD6))	// Toggle Teensy LED on.
#define LED_OFF		(PORTD	&= ~(1<<PD6))	// Toggle Teensy LED off.
#define CPU_16MHz       0x00				// Teensy clock speeds 16 MHz
#define CPU_PRESCALE(n)	(CLKPR = 0x80, CLKPR = (n)) // Teensy Hz setting for UART
#define F_CPU 16000000L						// For _ms_delay function
#define baud 9600							// UART
/////////// END Definitions: ////////////////////////////////////////////


// Main Function Decelerations:
void set_init(void);	// Set data direction for ports and initial values

///////////////////////////////////	Begin Main	/////////////////////////////////////////////

int main(void)
{
	// Initializations:
	set_init();
	char input;
 ValidateData();
    while(1)
    {
        //PORTD ^= 1<<6; //toggle LED to know we're alive
		/* Control Structure:
		1. Set PCR
		2. Run PCR
		*/
		
		printStr("Press 1 to set PCR \n"); //send 
		_delay_ms(2000);
			
		printStr("Press 2 to run PCR \n"); //send
		_delay_ms(2000);


		input = userInput(); // Get input from User.
		
		switch ( input ) {
			case 1:
			
			printStr("Set PCR \n"); //send 
			
			set_PCR();
			break;
			
			case 2:
			
			printStr("Run PCR \n"); //send
			
			runPCR();
			break;
			
			default:
			//powerSAVE();
			break;
		}
	}
}



void set_init(void){
	CPU_PRESCALE(CPU_16MHz);	//Set up UART
	timer_init();
	pwm_init();
	adc_init();
	uart_init();
	h_c_init(); 
	
	PORTB = 0b00000000; // Sets all PB pin values low.
	PORTF = 0b00000000; // Sets all PF pins low.
	PORTD = 0b00000000; // Sets all PD pins low.
	sei(); // Enable interrupts
}

void runPCR(void){
	int isTime = 0;
	int next = 0;
	int numTemps = 0;
	int timeAnneal = 40; // 40 seconds at 50C at 65C
	int timeDenat = 30; // 30 seconds above 95C
	int timeElong = 60; // 60 seconds at 70C and 80C
	
	holdAtTemp(50,timeAnneal);
	
	holdAtTemp(65,timeAnneal);
	
	holdAtTemp(70,timeElong);
	
	holdAtTemp(80,timeElong);
	
	holdAtTemp(96,timeDenat);
	



}