/*
 * menu.h
 *
 *  Created: 23/6/2022 23:48:35
 *  Author: Fran
 */ 


#ifndef MENU_H_
#define MENU_H_

	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <avr/io.h>
	#include "UART.h"
	#include "pwm.h"

	typedef enum {
		SELECT_COLOR,
		SET_COLOR,
		SET_BRIGHTNESS
	} CLI_MODE;
	
	void show_welcome();
	void show_menu(void);
	void update_menu(void);
	uint8_t get_must_print_flag(void);
	void set_must_print_flag(uint8_t value);
	CLI_MODE get_edition_mode(void);
	void set_edition_mode(CLI_MODE mode);

#endif