/*
 * CFile1.c
 *
 * Created: 23/6/2022 23:41:09
 *  Author: Fran
 */ 
#include "UART.h"

#define BAUD_PRESCALER (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

static volatile uint8_t BUFFER_RX[RX_BUFFER_LENGTH]; //Buffer para la recepcion
static volatile uint8_t BUFFER_TX[TX_BUFFER_LENGTH]; //Buffer para la transmision
static volatile uint8_t tx_writing_index = 0; //Indice de escritura para el buffer de transmision
static volatile uint8_t tx_reading_index = 0; //Indice de lectura para el buffer de transmision
static volatile uint8_t received_command = 0;  // Indica si se recibio un comando o no

/**
 * @brief Inicializa el UART
 */
void UART_init(uint8_t config) {
	UCSR0B = 0;
	UCSR0C = (1<<UCSZ01) | (1<<UCSZ00);
	UBRR0H = (unsigned char)(config>>8);
	UBRR0L = (unsigned char)config;
	UCSR0B |= (1<<TXEN0); //Activa la UART para transmision
	UCSR0B |= (1<<RXEN0); //Activa la UART para recepcion
	UCSR0B |= (1<<RXCIE0); //Activa las interrupciones de recepcion

	/* UCSR0B = 0;
	// Configuracion del baudrate
	UBRR0H = BAUD_PRESCALER  >> 8;
	UBRR0L = BAUD_PRESCALER;

	// Configuracion de la transmision y recepcion
	// ASYNC | PARITY | STOP | DATA
	UCSR0C = (0 << UMSEL00) | (0 << UPM00) | (0 << USBS0) | (1 << UCSZ01) | (1 << UCSZ00);


	// Activa la UART para transmision y recepcion	
	UCSR0B |= (1 << TXEN0) | (1 << RXEN0); */

	// Activa las interrupciones para la recepcion y transmision
	UART_RX_Interrupt_Enable();
	UART_TX_Interrupt_Enable();

	sei();
}

/**
 * @brief Habilita las interrupciones de transmision
 */
void UART_TX_Interrupt_Enable(void) {
	UCSR0B |= (1 << UDRIE0);
}

/**
 * @brief Deshabilita las interrupciones de transmision
 */
void UART_TX_Interrupt_Disable(void) {
	UCSR0B &= ~(1 << UDRIE0);
}

/**
 * @brief Habilita las interrupciones de recepcion
 */
void UART_RX_Interrupt_Enable(void) {
	UCSR0B |= (1 << RXCIE0);
}

/**
 * @brief Deshabilita las interrupciones de recepcion
 */
void UART_RX_Interrupt_Disable(void) {
	UCSR0B &= ~(1 << RXCIE0);
}

/**
 * @brief Recibe un caracter para escribir en el buffer de transmision
 * 
 * @param caracter Caracter a escribir
 */
void UART_write_char_buffer(uint8_t caracter) {
	if (((tx_writing_index + 1) % TX_BUFFER_LENGTH) != tx_reading_index) {
		BUFFER_TX[tx_writing_index] = caracter;
		// Incrementa el indice de escritura o lo reinicia si llega al final del buffer
		tx_writing_index = (tx_writing_index+1) % (TX_BUFFER_LENGTH);
	}	else {
		//ERROR el buffer esta lleno
	}
}

/**
 * @brief Recibe un string para escribir en el buffer de transmision
 * 
 * @param cadena String a escribit
 */
void UART_write_string_buffer(uint8_t * cadena) {
	uint8_t i;
	for (i = 0; cadena[i] != '\0'; i++) {
		UART_write_char_buffer(cadena[i]);
	}
}

/**
 * @brief Lee una cadena de caracteres desde el buffer de recepcion
 * 
 * @param cadena String donde se guardara la cadena leida
 */
void UART_get_string_from_buffer(uint8_t * cadena) {
	uint8_t i = 0;
	while (BUFFER_RX[i] != '\0') {
		cadena[i] = BUFFER_RX[i];
		i++;
	}
}

/**
 * @brief Interrupcion de recepcion
 */
ISR(USART_RX_vect) {
	static uint8_t i = 0;
	BUFFER_RX[i] = UDR0;
	// ¿Se llegó al final de la cadena?
	if (BUFFER_RX[i] == '\r') {
		// Remplaza el valor por un vacio '\0'
		BUFFER_RX[i] = '\0';
		// Indica que se recibió un comando
		received_command = 1;
		// Reinicia el contador de lectura
		i = 0;
	} else if (i == (RX_BUFFER_LENGTH - 1)) {
			// Si se llegó al final del buffer, se reinicia el contador
			i = 0;
	} else {
		i = (i + 1) % (TX_BUFFER_LENGTH);
	}
}

/**
 * @brief Interrupcion para indicar que se puede transmitir en la UART
 */
ISR(USART_UDRE_vect) {
	cli();
	// ¿Hay algo que transmitir?
	if (tx_reading_index != tx_writing_index) {
		// Transmite el siguiente caracter
		UDR0 = BUFFER_TX[tx_reading_index];
		// Incrementa el indice de lectura o lo resetea en el caso de llegar al final del buffer
		tx_reading_index = (tx_reading_index+1)%(TX_BUFFER_LENGTH-1);
	} else	{
		// Deshabilita la interrupcion de transmision
		UART_TX_Interrupt_Disable();
	}
	// Incrementa el indice de lectura o lo resetea en el caso de llegar al final del buffer
	sei();
}

uint8_t get_received_command(void) {
	return received_command;
}

void set_received_command(uint8_t valor) {
	received_command= valor;
}