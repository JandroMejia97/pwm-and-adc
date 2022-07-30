/*
 * adc.h
 *
 * Created: 29/07/2022 03:52:20 p. m.
 *  Author: Alejandro Mejía
 */ 


#ifndef ADC_H_
#define ADC_H_
	#include <avr/io.h>

  void adc_init(void);
  uint16_t adc_read(uint8_t adc_channel);
#endif /* ADC_H_ */

