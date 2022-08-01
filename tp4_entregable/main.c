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
	timer_init();
	sei();

	while (1) {
		adc_read();
		if (get_adc_read_completed()) {
			uint8_t valor = map_to(get_adc_value(), 0, 255, 0, 255);
			set_adc_read_completed(0);
			//UART_send_byte(valor);
			OCR1A = ICR1 - (255 * valor / 64);
			OCR1B = ICR1 - (255 * valor / 64);
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
