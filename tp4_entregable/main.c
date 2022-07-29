/*
 * main.c
 *
 * Created: 7/11/2022 2:35:52 PM
 *  Author: Barcala
 */

#include <avr/io.h>

#define F_CPU 16000000UL
uint16_t timer1_prescaler = 64;
uint16_t strobe_frequency = 50, strobe_duty_cycle = 20;

int main(void) {
	// Set PB1 and PB2 to be outputs
	DDRB |= (1 << PINB1) | (1 << PINB2);
	
	// Clear Timer/Counter Control Registers
	TCCR1A = 0;
	TCCR1B = 0;
	
	// Set non-inverting mode
	TCCR1A |= (1 << COM1A1);
	
	// Set fast PWM - mode 14
	TCCR1A |= (1 << WGM11);
	TCCR1B |= (1 << WGM13) | (1 << WGM12);
	
	// Prescaler 8
	TCCR1B |= (1 << CS11) | (1 << CS10);
	
	// Set PWM frequency/top value
	ICR1 = 4999;
	OCR1A = ICR1 / (100 / strobe_duty_cycle);
	
    while(1) {
        //TODO:: Please write your application code 
    }
}