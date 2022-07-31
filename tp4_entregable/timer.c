/*
 * timer.c
 *
 * Created: 29/07/2022 03:52:30 p. m.
 *  Author: Alejandro Mejía
 */
#include "timer.h"

const uint16_t timer1_prescaler = 64;
const uint16_t strobe_frequency = 50, strobe_duty_cycle = 20;

void timer_init() {
	// Set PB1, PB2 and PB5 to be outputs
	DDRB |= (1 << PINB1) | (1 << PINB2) | (1 << PINB5);

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
}
