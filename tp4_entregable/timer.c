/*
 * timer.c
 *
 * Created: 29/07/2022 03:52:30 p. m.
 *  Author: Alejandro Mejía
 */
#include "timer.h"

const uint16_t timer1_prescaler = 64;
const uint16_t strobe_frequency = 50, strobe_duty_cycle = 20;

/**
 * @brief Inicializa el timer1
 */
void timer_init() {
	// Set PB1, PB2 and PB5 to be outputs
	DDRB |= (1 << PINB1) | (1 << PINB2) | (1 << PINB5);
	PORTB = 0x00;

	// Clear Timer/Counter Control Registers
	TCCR1A = 0;
	TCCR1B = 0;

	// Set inverting mode channel A
	TCCR1A |= (1 << COM1A1) | (1 << COM1A0);
	// Set inverting mode channel B
	TCCR1A |= (1 << COM1B1) | (1 << COM1B0);

	// Set fast PWM - mode 14
	TCCR1A |= (1 << WGM11);
	TCCR1B |= (1 << WGM13) | (1 << WGM12);

	// Prescaler 64
	TCCR1B |= (1 << CS11) | (1 << CS10);

	// Set PWM frequency/top value
	ICR1 = 4999;
	// Set duty cycle
	OCR1A = (ICR1 / 2) - 1;
	OCR1B = (ICR1 / 2) - 1;
}

uint8_t map_to(uint8_t x, uint8_t in_min, uint8_t in_max, uint8_t out_min, uint8_t out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}