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
			OCR1A = (duty_cycle * (ICR1 + 1))  - 1;
			OCR1B = (duty_cycle * (ICR1 + 1))  - 1;
		}
		/* SEOS_Dispatch_Tasks();
		if (get_received_command()) {
			//update_menu();
			set_received_command(0);
		}
		if (get_transmit_data()) {
			UART_TX_Interrupt_Enable();
			set_transmit_data(0);
		} */
	}
}
