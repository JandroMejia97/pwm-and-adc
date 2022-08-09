#include "pwm.h"

static uint8_t red_color = 255;
static uint8_t green_color = 255;
static uint8_t blue_color = 255;
static uint8_t brightness_percentage = 100;

void timer0_init(void);
void timer1_init(void);
uint16_t map(uint16_t x, uint16_t in_min, uint16_t in_max, uint16_t out_min, uint16_t out_max);

/**
 * @brief Inicializa el PWM
 */
void pwm_init() {
	// Set PB1, PB2 and PB5 to be outputs
	DDRB |= (1 << PINB1) | (1 << PINB2) | (1 << PINB5);
	PORTB = 0x00;

	pwm_timer1_init();
	pwm_timer0_init();

	OCR0A = pwm_get_brightness_value(red_color);
	OCR1B = pwm_get_brightness_value(green_color);
	OCR1A = pwm_get_brightness_value(blue_color);
}

/**
 * @brief Inicializa el timer0
 */
void pwm_timer0_init() {
	// Set inverting mode channel A timer0
	TCCR0A |= (1 << COM0A1) | (1 << COM0A0);
	// Set fast PWM - mode 3
	TCCR0A |= (1 << WGM01) | (1 << WGM00);
	// 1024 prescaler, frecuencia de 61Hz
	TCCR0B |= (1 << CS02) | (1 << CS00);

	// Enable interrupts for timer 0
	TIMSK0 |= (1 << OCIE0A) | (1 << TOIE0);
}

/**
 * @brief Inicializa el timer1
 */
void pwm_timer1_init() {
	// Clear Timer/Counter Control Registers
	TCCR1A = 0;
	TCCR1B = 0;

	// Set inverting mode channel A
	TCCR1A |= (1 << COM1A1) | (1 << COM1A0);
	// Set inverting mode channel B
	TCCR1A |= (1 << COM1B1) | (1 << COM1B0);

	// Set fast PWM - mode 5
	TCCR1A |= (1 << WGM10);
	TCCR1B |= (1 << WGM12);

	// Prescaler 1024
	TCCR1B |= (1 << CS12) | (1 << CS10);

	// Set PWM frequency/top value
	ICR1 = 4098;
}

/**
 * @brief Establece el color rojo y actualiza el PWM
 * 
 * @param value Valor del color rojo
 */
void pwm_set_red_color(uint8_t value) {
	red_color = value;
	OCR0A = pwm_get_brightness_value(red_color);
}

/**
 * @brief Establece el color verde y actualiza el PWM
 * 
 * @param value Valor del color verde
 */
void pwm_set_green_color(uint8_t value) {
	green_color = value;
	OCR1B = pwm_get_brightness_value(value);
}

/**
 * @brief Establece el color azul y actualiza el PWM
 * 
 * @param value Valor del color azul
 */
void pwm_set_blue_color(uint8_t value) {
	blue_color = value;
	OCR1A = pwm_get_brightness_value(value);
}

/**
 * @brief Establece el porcentaje de brillo y actualiza los colores del PWM
 * 
 * @param value Valor del porcentaje de brillo
 */
void pwm_set_brightness_percentage(uint8_t value) {
	brightness_percentage = value;
	pwm_set_red_color(red_color);
	pwm_set_green_color(green_color);
	pwm_set_blue_color(blue_color);
}

/**
 * @brief Obtiene el porcentaje de brillo
 * 
 * @return uint8_t Porcentaje de brillo
 */
uint8_t pwm_get_brightness_percentage() {
	return brightness_percentage;
}

/**
 * @brief Calcula el valor de brillo para un color
 * 
 * @return uint8_t Valor de brillo
 */
uint8_t pwm_get_brightness_value(uint8_t value) {
	return (uint8_t) value * brightness_percentage / 100;
}

/**
 * @brief Interrupcion OVF del timer0
 */
ISR(TIMER0_OVF_vect) {
	pwm_set_red_color(red_color);
	PORTB &= ~(1 << PINB5);
}

/**
 * @brief Interrupcion COMPA del timer0
 */
ISR(TIMER0_COMPA_vect) {
	PORTB |= (1 << PINB5);
}

uint16_t map(uint16_t x, uint16_t in_min, uint16_t in_max, uint16_t out_min, uint16_t out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
