#include "menu.h"

static uint8_t menu_msg_1[] = "Regulador de intensidad de LED RGB\n\r";
static uint8_t menu_msg_2[] = "Ingrese el color deseado (usando decimales 0-255) en el formato: R,G,B.\n\r";
static uint8_t menu_msg_3[] = "Por ejemplo: Para mostrar el color rojo, ingrese: 255,0,0\n\r";
static uint8_t menu_msg_4[] = "Nota: Use el potenciometro para regular el brillo del LED\n\r";
static uint8_t error_msg[]= "Comando no valido\n\r";
static uint8_t info_msg[] = "Brillo: ";
static uint8_t red_color[] ="ROJO\n\r";
static uint8_t green_color[] ="VERDE\n\r";
static uint8_t blue_color[] ="AZUL\n\r";

static uint8_t transmit_data = 0;
char hum [5];
char temp [5];
uint8_t must_print = 0;

/**
 * @brief Muestra el menu en el puerto serie
 */
void show_menu(void) {
	UART_write_string_buffer(menu_msg_1);
	UART_write_string_buffer(menu_msg_2);
	UART_write_string_buffer(menu_msg_3);
	UART_write_string_buffer(menu_msg_4);
	transmit_data = 1;
}

uint8_t get_transmit_data(void) {
	return transmit_data;
}

void set_transmit_data(uint8_t valor) {
	transmit_data = valor;
}

/**
 * @brief Actualiza el menu en el puerto serie
 */
void update_menu() {
	uint8_t input[1]="";
	UART_get_string_from_buffer(input);
	if (strcmp((const char*) input, (const char*) "R") == 0 || strcmp((const char*) input, (const char*) "r") == 0){
		UART_write_string_buffer(info_msg);
		UART_write_string_buffer(red_color);
		transmit_data = 1;
		must_print = 1;
	}	else if (strcmp((const char*) input, (const char*) "G") == 0 || strcmp((const char*) input, (const char*) "g") == 0){
		UART_write_string_buffer(info_msg);
		UART_write_string_buffer(green_color);
		transmit_data = 1;
		must_print = 1;
	}	else if (strcmp((const char*) input, (const char*) "B") == 0 || strcmp((const char*) input, (const char*) "b") == 0){
		UART_write_string_buffer(info_msg);
		UART_write_string_buffer(blue_color);
		transmit_data = 1;
		must_print = 1;
	} else {
		UART_write_string_buffer(error_msg);
		transmit_data = 0;
		must_print = 0;
	}

}

/**
 * @brief Indica si se debe imprimir información en el puerto serie
 * @return uint8_t 1 si se debe imprimir, 0 en caso contrario
 */
uint8_t must_print_flag() {
	return must_print;
}