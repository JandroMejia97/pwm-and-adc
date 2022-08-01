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
	float get_ocr_value(float duty_cycle);
	void set_red_color(float duty_cycle);
	void set_green_color(float duty_cycle);
	void set_blue_color(float duty_cycle);
#endif /* PWM_H_ */