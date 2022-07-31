/*
 * adc.h
 *
 * Created: 29/07/2022 03:52:20 p. m.
 *  Author: Alejandro Mejía
 */ 

#ifndef ADC_H_
#define ADC_H_
  #include <avr/io.h>
  #include <avr/interrupt.h>

  void adc_init(void);
  void adc_read(void);
  void set_adc_read_completed(uint8_t);
  uint8_t get_adc_read_completed(void);
  uint8_t get_adc_value(void);
#endif /* ADC_H_ */

