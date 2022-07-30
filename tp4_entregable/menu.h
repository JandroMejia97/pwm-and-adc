/*
 * menu.h
 *
 *  Created: 23/6/2022 23:48:35
 *  Author: Fran
 */ 


#ifndef MENU_H_
#define MENU_H_

	#include "stdint.h"
	#include "string.h"
	#include <avr/io.h>
	#include "UART.h"
	
	void show_menu(void);
	void update_menu(void);
	void set_transmit_data(uint8_t value);
	uint8_t get_transmit_data(void);
	uint8_t must_print_flag(void);

#endif