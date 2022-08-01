#include "pwm.h"
void pwm_init() {
	// Set PB1, PB2 and PB5 to be outputs
	DDRB |= (1 << PINB1) | (1 << PINB2) | (1 << PINB5);
	//PORTB = 0b00000110;

	// Clear Timer/Counter Control Registers
	TCCR1A = 0;
	TCCR1B = 0;

	// Set non-inverting mode
	TCCR1A |= (1 << COM1A1) | (1 << COM1B1);

	// Set fast PWM - mode 14
	TCCR1A |= (1 << WGM11);
	TCCR1B |= (1 << WGM13) | (1 << WGM12);

	// Prescaler 64
	TCCR1B |= (1 << CS10) | (1 << CS11);

	// Set PWM frequency/top value
	ICR1 = 4999;
	
	// OCR1A = ;
	OCR1B = ICR1 * 0.01;
	OCR1A = ICR1 * 0.01;
}