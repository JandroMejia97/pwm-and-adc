/*
 * main.h
 *
 * Created: 29/07/2022 03:18:41 p. m.
 *  Author: Alejandro Mejía
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
	#include "seos.h"
	#include "timer.h"
	#include "adc.h"
#endif