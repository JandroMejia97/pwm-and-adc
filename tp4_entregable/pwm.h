/*
 * pwm.h
 *
 * Created: 31/7/2022 17:39:33
 *  Author: Fran
 */ 


#ifndef PWM_H_
#define PWM_H_
	#include <avr/io.h>
	void pwm_init(void);
	void set_duty_cycle(float duty_cycle, uint8_t color);
#endif /* PWM_H_ */