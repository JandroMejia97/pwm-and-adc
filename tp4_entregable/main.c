/*
 * GccApplication2.c
 *
 * Created: 31/7/2022 17:36:40
 * Author : Fran
 */ 

#include <avr/io.h>
#include "main.h"

int main(void) {
	pwm_init();
	adc_init();
	sei();
	while (1) {
		adc_read();
		if (get_adc_read_completed()) {
			float duty_cycle = get_adc_percentage_value();
			set_adc_read_completed(0);
			//UART_send_byte(valor);
			set_red_color(duty_cycle);
			set_green_color(duty_cycle);
			set_blue_color(duty_cycle);
		}
	}
}
