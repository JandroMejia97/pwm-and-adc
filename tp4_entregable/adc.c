#include "adc.h"

static volatile uint8_t data = 0;
uint8_t adc_read_completed = 0;

/**
 * @brief Initializes the ADC
 */
void adc_init(void) {
  // Configuro como entrada analógica el pin PC3
  DIDR0 |= 1 << ADC3D;
  // Referencia de AVCC | Justificación de la conversión: right-adjust
  ADMUX = 1 << REFS0;
  // Prescaler de 128, para una frecuencia de 125KHz (el rendimiento es mejor hasta 200KHz)
  ADCSRA = (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
  // Habilito la ADC | Habilito la interrupción de ADC
  ADCSRA |= (1 << ADEN) | (1 << ADIE);
}

/**
 * @brief Inicia la conversión de ADC
 */
void adc_read(void) {
  ADCSRA |= 1 << ADSC;
  adc_read_completed = 1;
}

void set_adc_read_completed(uint8_t valor) {
  adc_read_completed = valor;
}

uint8_t get_adc_read_completed(void) {
  return adc_read_completed;
}

uint8_t get_adc_value(void) {
  return data;
}

/**
 * @brief Interrupción de ADC
 */
ISR(ADC_vect) {
  // Devuelvo el resultado (8 bits, parte baja)
  data = ADCL;
}