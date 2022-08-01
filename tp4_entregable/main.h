/*
 * main.h
 *
 * Created: 31/7/2022 17:38:16
 *  Author: Fran
 */ 

#ifndef MAIN_H_
#define MAIN_H_
	#ifndef F_CPU
	#define F_CPU 16000000UL
	#endif
	#include <avr/io.h>
	#include <avr/interrupt.h>
	#include <util/delay.h>
	#include "UART.h"
	#include "menu.h"
	#include "pwm.h"
	#include "adc.h"
#endif