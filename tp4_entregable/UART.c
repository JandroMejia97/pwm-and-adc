/*
 * CFile1.c
 *
 * Created: 23/6/2022 23:41:09
 *  Author: Fran
 */ 
#include "UART.h"

static volatile uint8_t BUFFER_RX[RX_BUFFER_LENGTH]; //Buffer para la recepcion
static volatile uint8_t BUFFER_TX[TX_BUFFER_LENGTH]; //Buffer para la transmision
static volatile uint8_t tx_writing_index = 0; //Indice de escritura para el buffer de transmision
static volatile uint8_t tx_reading_index = 0; //Indice de lectura para el buffer de transmision
static volatile uint8_t received_command = 0;  // Indica si se recibio un comando o no

/**
 * @brief Inicializa el UART
 * @param baudrate Baudrate a utilizar
 */
void UART_init(uint8_t config) {
	UCSR0B = 0;
	UCSR0C = (1<<UCSZ01) | (1<<UCSZ00);
	UBRR0H = (unsigned char)(config>>8);
	UBRR0L = (unsigned char)config;
	UCSR0B |= (1<<TXEN0); //Activa la UART para transmision
	UCSR0B |= (1<<RXEN0); //Activa la UART para recepcion
	UCSR0B |= (1<<RXCIE0); //Activa las interrupciones de recepcion
	TCCR1B |= (1 << WGM12);				// Modo CTC con OCR1A
	TCCR1B |= (1 << CS12);				// Prescaler = F_CPU/256
	OCR1A = 3125;						// seteo el contador en 3125
	TIMSK1 |= (1 << OCIE1A);			// habilito interrupci n del contador OCR1A
	sei();
}

/**
 * @brief Habilita las interrupciones de transmision
 */
void UART_TX_Interrupt_Enable(void) {
	UCSR0B |= (1<<UDRIE0);
}

/**
 * @brief Deshabilita las interrupciones de transmision
 */
void UART_TX_Interrupt_Disable(void) {
	UCSR0B &= ~(1<<UDRIE0);
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
	uint8_t i;
	for (i = 0; BUFFER_RX[i] != '\0'; i++) {
		cadena[i] = BUFFER_RX[i];
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
		i++;
	}
}

/**
 * @brief Interrupcion para indicar que se puede transmitir en la UART
 */
ISR(USART_UDRE_vect) {
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
}

uint8_t get_received_command(void) {
	return received_command;
}

void set_received_command(uint8_t valor) {
	received_command= valor;
}