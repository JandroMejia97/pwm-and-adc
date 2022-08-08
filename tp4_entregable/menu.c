#include "menu.h"

static uint8_t menu_msg_1[] = "REGULADOR DE INTENSIDAD DE LED RGB\n\r";
static uint8_t menu_msg_2[] = "INGRESA LA INICIAL DEL COLOR A ESTABLECER: R, G o B.\n\r";
static uint8_t menu_msg_3[] = "NOTA: USE EL POTENCIOMETRO PARA REGULAR EL BRILLO DEL LED.\n\r";
static uint8_t info_msg_1[] = "COLOR %s, VALOR ACTUAL %d.\n\r";
static uint8_t info_msg_2[] = "INGRESE EL NUEVO VALOR (0-255):\n\r";
static uint8_t info_msg_3[] = "BRILLO: %d%%.\n\r";
static uint8_t error_msg_1[] = "COMANDO NO VALIDO.\n\r";
static uint8_t error_msg_2[] = "VALOR NO VALIDO.\n\r";

static uint8_t red_msg[] = "ROJO";
static uint8_t blue_msg[] = "AZUL";
static uint8_t green_msg[] = "VERDE";

static uint8_t colors[3] = {255, 255, 255};

typedef enum {
	RED,
	GREEN,
	BLUE
} RGB_COLORS;

static uint8_t selected_color = -1;
static int16_t get_value(uint8_t* input);
static uint8_t * get_text_color(RGB_COLORS color);

/**
 * Modo de edicion del menu.
 */
static CLI_MODE edition_mode = SELECT_COLOR;
/**
 * Bandera para indicar si hay datos para transmitir por UART
 */
static uint8_t must_print = 0;

/**
 * @brief Muestra una bienvenida al usuario
 */
void show_welcome(void) {
	UART_write_string_buffer(menu_msg_1);
	show_menu();
}

/**
 * @brief Muestra el menu en el puerto serie
 */
void show_menu(void) {
	UART_write_string_buffer(menu_msg_2);
	UART_write_string_buffer(menu_msg_3);
	must_print = 1;
}

/**
 * @brief Actualiza el menu en el puerto serie
 */
void update_menu() {
	char input[4] = "";
	UART_get_string_from_buffer((uint8_t *) input);

	switch(edition_mode) {
		case SELECT_COLOR: ;
			if (!strcmp((const char *) input, (const char *) "R")) {
				selected_color = RED;
			} else if (!strcmp((const char *) input, (const char *) "G")) {
				selected_color = GREEN;
			} else if (!strcmp((const char *) input, (const char *) "B")) {
				selected_color = BLUE;
			}

			if (selected_color != -1) {
				char msg[32];
				sprintf(msg, (const char*) info_msg_1, get_text_color(selected_color), colors[selected_color]);
				UART_write_string_buffer((uint8_t *) msg);
				UART_write_string_buffer(info_msg_2);
				must_print = 1;
				edition_mode = SET_COLOR;
			} else {
				UART_write_string_buffer(error_msg_1);
				show_menu();
			}
			break;
		case SET_COLOR: ;
			int16_t value = get_value((uint8_t *) input);
			if (value > -1) {
				switch(selected_color) {
					case RED:
						colors[selected_color] = value;
						pwm_set_red_color(value);
						break;
					case GREEN:
						colors[selected_color] = value;
						pwm_set_green_color(value);
						break;
					case BLUE:
						colors[selected_color] = value;
						pwm_set_blue_color(value);
						break;
				}
				edition_mode = SELECT_COLOR;
				selected_color = 0;
				show_menu();
			} else {
				UART_write_string_buffer(error_msg_2);
				UART_write_string_buffer(info_msg_2);
				must_print = 1;
			}
			break;
		case SET_BRIGHTNESS: ;
			uint8_t brightness = pwm_get_brightness_percentage();
			char msg[15];
			sprintf(msg, (const char*)info_msg_3, brightness);
			UART_write_string_buffer((uint8_t *)msg);
			edition_mode = SELECT_COLOR;
			must_print = 1;
			break;
	}

}

static int16_t get_value(uint8_t * input) {
	uint8_t digits = strlen((const char *) input);
	uint16_t value = 0;

	if (digits <= 0 || digits > 3) {
		return -1;
	}
	for (uint8_t i = 0; i < digits; i++) {
		if (input[i] < '0' || input[i] > '9') {
			return -1;
		}
		value = value * 10 + (input[i] - '0');
	}
	if (value > 255) {
		return -1;
	}

	return value;
}

/**
 * @brief Indica si se debe imprimir información en el puerto serie
 * @return uint8_t 1 si se debe imprimir, 0 en caso contrario
 */
uint8_t get_must_print_flag() {
	return must_print;
}

void set_must_print_flag(uint8_t valor) {
	must_print = valor;
}

static uint8_t * get_text_color(RGB_COLORS color) {
	uint8_t * msg = NULL;
	switch(color) {
		case RED:
			msg = red_msg;
			break;
		case GREEN:
			msg = green_msg;
			break;
		case BLUE:
			msg = blue_msg;
			break;
	}
	return msg;
}

CLI_MODE get_edition_mode() {
	return edition_mode;
}

void set_edition_mode(CLI_MODE mode) {
	edition_mode = mode;
}