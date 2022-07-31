/*
 * seos.c
 *
 * Created: 29/07/2022 03:25:27 p. m.
 *  Author: Alejandro Mejía
 */ 
#include "seos.h"

volatile unsigned char tick_flag = 0;
static unsigned char timer_counter = 0;

void SEOS_Schedule_Tasks(void) {
	if (++timer_counter == 20) { // Cada 1 segundo
		tick_flag = 1;
		timer_counter = 0;
	}
}


void SEOS_Dispatch_Tasks (void) {
	if (tick_flag && must_print_flag()) {
    // Lectura del potenciómetro
		// Cambiar la intensidad del LED
		// Impresión del valor leído
		tick_flag = 0;
	}
}

ISR (TIMER1_COMPA_vect) {
	SEOS_Schedule_Tasks();
}
