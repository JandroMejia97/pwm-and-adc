#include "acd.h"


void adc_init(void) {
  // PINC3 como entrada
  DDRC &= ~(1 << PINC3);
  // Referencia de AVCC | Justificación de la conversión: right-adjust
  ADMUX = (1 << REFS0);
  // Prescaler de 128, para una frecuencia de 125KHz (el rendimiento es mejor hasta 200KHz)
  // Habilito la ADC | ADC Prescaler = 128
  ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}

uint16_t adc_read(uint8_t adc_channel) {
  // Selecciono el canal de entrada
  ADMUX = (ADMUX & 0xF0) | (adc_channel & 0x0F);
  // Inicio la conversión
  ADCSRA |= (1 << ADSC);
  // Espero a que termine la conversión
  while (~(ADCSRA & (1 << ADIF)));
  // Limpio el flag de conversion
  ADCSRA |= (1 << ADIF);
  // Devuelvo el resultado
  return ADC;
}