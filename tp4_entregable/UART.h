/*
 * uart.h
 *
 * Created: 23/6/2022 23:39:26
 *  Author: Fran
 */ 


#ifndef UART_H_
#define UART_H_

	#include <stdint.h>
	#include <avr/io.h>
	#include <avr/interrupt.h>
	
	#define RX_BUFFER_LENGTH 6
	#define TX_BUFFER_LENGTH 200

	#ifndef F_CPU
		#define F_CPU 16000000UL
	#endif

	#ifndef USART_BAUDRATE
		#define USART_BAUDRATE 9600
	#endif
	
	void UART_init(uint8_t config);
	void UART_TX_Interrupt_Disable(void);
	void UART_TX_Interrupt_Enable(void);
	void UART_RX_Interrupt_Disable(void);
	void UART_RX_Interrupt_Enable(void);
	void UART_write_char_buffer(uint8_t caracter);
	void UART_write_string_buffer(uint8_t * cadena);
	void UART_get_string_from_buffer(uint8_t* cadena);
	uint8_t get_received_command(void);
	void set_received_command(uint8_t valor);
#endif