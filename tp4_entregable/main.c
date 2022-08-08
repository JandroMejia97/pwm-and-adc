/*
 * GccApplication2.c
 *
 * Created: 31/7/2022 17:36:40
 * Author : Fran
 */ 

#include <avr/io.h>
#include "main.h"
static volatile uint16_t prev_adc_value = 0;

int main(void) {
	UART_init(0x33);
	pwm_init();
	adc_init();
	show_welcome();
	sei();
	while (1) {
		if (get_received_command()) {
			update_menu();
			set_received_command(0);
		} 

		adc_read();
		if (adc_get_read_completed() && adc_get_value() != prev_adc_value) {
			uint8_t duty_cycle = adc_get_percentage_value() * 100;
			pwm_set_brightness_percentage(duty_cycle);
			adc_set_read_completed(0);
			if (get_edition_mode() == SELECT_COLOR) {
				set_edition_mode(SET_BRIGHTNESS);
				update_menu();
			}
			prev_adc_value = adc_get_value();
		}

		if (get_must_print_flag()) {
			UART_TX_Interrupt_Enable();
			set_must_print_flag(0);
		}
	}
}
