/*
 * tp4_entregable.c
 *
 * Created: 7/11/2022 2:35:52 PM
 * Author : Alejandro Mejía
 */ 


#include "main.h"

int main(void) {
	//UART_init(0x33);
	//show_menu();
	timer_init();

  while (1) {
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
