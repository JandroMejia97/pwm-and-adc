#include "adc.h"

static volatile uint16_t data = 0;
uint8_t adc_read_completed = 0;

/**
 * @brief Initializes the ADC
 */
void adc_init(void) {
  // Configuro como entrada analógica el pin PC3
  DIDR0 |= 1 << ADC3D;
  // Referencia de AVCC | Justificación de la conversión: right-adjust
  ADMUX = (1 << REFS0) | (0 << ADLAR);
  // Selecciono el canal 3 del ADC
  ADMUX |= 1 << MUX0 | 1 << MUX1;
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
}

void set_adc_read_completed(uint8_t valor) {
  adc_read_completed = valor;
}

uint8_t get_adc_read_completed(void) {
  return adc_read_completed;
}

uint16_t get_adc_value(void) {
  return data;
}

/**
 * @brief Interrupción de ADC
 */
ISR(ADC_vect) {
  // Devuelvo el resultado (8 bits, parte baja)
  uint8_t low = ADCL;
  // Devuelvo el resultado (8 bits, parte alta)
  uint8_t high = ADCH;
  // Concateno los dos resultados
  data = (high << 8) | low;
  data = 1024 - data;
  adc_read_completed = 1;
}