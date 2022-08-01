#include "pwm.h"

/**
 * @brief Inicializa el timer1
 */
void pwm_init() {
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

void set_duty_cycle(float duty_cycle, uint8_t color) {
	uint8_t ocr_value = (duty_cycle * (ICR1 + 1))  - 1;
	switch (color) {
		case 'R':
			PORTB &= ~(1 << PINB1);
			break;
		case 'G':
		  OCR1B = ocr_value;
			break;
		case 'B':
			OCR1A = ocr_value;
			break;
	}
}

