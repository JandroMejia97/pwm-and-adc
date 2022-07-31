#include "acd.h"

/**
 * @brief Initializes the ADC
 */
void adc_init(void) {
  // PINC3 como entrada
  DDRC &= ~(1 << PINC3);
  // Referencia de AVCC | Justificación de la conversión: right-adjust
  ADMUX = (1 << REFS0);
  // Prescaler de 128, para una frecuencia de 125KHz (el rendimiento es mejor hasta 200KHz)
  // Habilito la ADC | Habilito la interrupción de ADC | ADC Prescaler = 128
  ADCSRA = (1 << ADEN) | (1 << ADIE) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
  // Deshabilito la entrada digital en el pin ADC3
  DIDR0 |= 1 << ADC3D;
}

/**
 * @brief Lee el ADC y devuelve el valor leído
 * 
 * @param adc_channel Número del canal a leer
 * @return uint16_t Valor leído
 */
uint8_t adc_read() {
  // Inicio la conversión
  ADCSRA |= (1 << ADSC);
  // Espero a que termine la conversión
  while (~(ADCSRA & (1 << ADIF)));
  // Limpio el flag de conversion
  ADCSRA |= (1 << ADIF);
  // Devuelvo el resultado (8 bits, parte baja)
  return ADCL;
}