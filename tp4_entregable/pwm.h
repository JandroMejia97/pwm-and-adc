/*
 * pwm.h
 *
 * Created: 31/7/2022 17:39:33
 *  Author: Fran
 */ 


#ifndef PWM_H_
#define PWM_H_
	#include <avr/io.h>
	#include <avr/interrupt.h>
	void pwm_init(void);
	void pwm_timer0_init(void);
	void pwm_timer1_init(void);
	void pwm_set_red_color(uint8_t);
	void pwm_set_green_color(uint8_t);
	void pwm_set_blue_color(uint8_t);
	void pwm_set_brightness_percentage(uint8_t);
	uint8_t pwm_get_brightness_percentage();
	uint8_t pwm_get_brightness_value(uint8_t);
#endif /* PWM_H_ */