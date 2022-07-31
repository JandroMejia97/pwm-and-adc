/*
 * timer.h
 *
 * Created: 29/07/2022 03:52:20 p. m.
 *  Author: Alejandro Mejía
 */ 


#ifndef TIMER_H_
#define TIMER_H_
	#include <avr/io.h>

  void timer_init(void);
  uint8_t map_to(uint8_t x, uint8_t in_min, uint8_t in_max, uint8_t out_min, uint8_t out_max);
#endif /* TIMER_H_ */