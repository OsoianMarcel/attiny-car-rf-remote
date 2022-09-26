#include "rf433.h"

// The bits are written from low to high in an array of uint8_t.
// One command contains 66 bits (KEELOQ). 
// The radio receivers usually ignore the resent command, that's why
// we need to store at least 2 commands to make sure our transmitter will work property.
// So each time the button is pressed the transmitter send a new command.
const uint8_t rf433_codes[][RF433_CODE_BYTES] = {
	{0b00011100, 0b11100000, 0b00010011, 0b10101000, 0b11001000, 0b01101110, 0b00001111, 0b00100000, 0b11}, // [0] #A
	{0b11111110, 0b11001010, 0b10010111, 0b00101100, 0b11001000, 0b01101110, 0b00001111, 0b00100000, 0b11}, // [1] #B
	{0b01111110, 0b10011010, 0b11011111, 0b00001000, 0b11001000, 0b01101110, 0b00001111, 0b00100000, 0b11}, // [2] #1
	{0b11001011, 0b01011101, 0b01000100, 0b01001001, 0b11001000, 0b01101110, 0b00001111, 0b00100000, 0b11}, // [3] #2
	{0b01110010, 0b00111000, 0b11010001, 0b10101100, 0b11001000, 0b01101110, 0b00001111, 0b00100000, 0b11}, // [4] #3
	{0b00000101, 0b10001111, 0b00010111, 0b10000111, 0b11001000, 0b01101110, 0b00001111, 0b00100000, 0b11}, // [5] #4
	{0b11010100, 0b01111100, 0b11000010, 0b10001001, 0b11001000, 0b01101110, 0b00001111, 0b00100000, 0b11}, // [6] #5
	{0b00011101, 0b11101100, 0b11001010, 0b00110000, 0b11001000, 0b01101110, 0b00001111, 0b00100000, 0b11}  // [7] #6
};

const uint8_t rf433_codes_count = sizeof(rf433_codes) / sizeof(rf433_codes[0]);

const uint8_t first_logic_level = (RF433_INVERTED == 1) ? 0 : 1;
const uint8_t second_logic_level = (RF433_INVERTED == 1) ? 1 : 0;

void rf433_init(Rf433_Scope *scope) {
	*scope->DDR |= (1 << scope->PIN);
	*scope->PORT &= ~((1 << scope->PIN));
}

void rf433_uninit(Rf433_Scope *scope) {
	*scope->DDR &= ~((1 << scope->PIN));
	*scope->PORT &= ~((1 << scope->PIN));
}

void rf433_pin_control(Rf433_Scope *scope, uint8_t state) {
	// On
	if (state == 1) {
		*scope->PORT |= (1 << scope->PIN);
		return;
	}
	
	// Off
	*scope->PORT &= ~(1 << scope->PIN);
}

const uint8_t* rf433_get_next_code(void) {
	static uint8_t rb = 0;

	const uint8_t *code = rf433_codes[rb];

	if (rb < rf433_codes_count - 1) {
		rb++;
	} else {
		rb = 0;
	}

	return code;
}

void rf433_send_code(Rf433_Scope *scope, const uint8_t *rf_code) {
	uint8_t i, j;

	// Preamble (23 Te)
	for (i = 0; i < 12; i++) {
		rf433_pin_control(scope, first_logic_level);
		_delay_us(400);
		rf433_pin_control(scope, second_logic_level);
		if (i != 11) {
			_delay_us(400);
		}
	}

	// Header (10 Te)
	_delay_us(4000);

	// Data (198 Te)
	for (i = 0; i < RF433_CODE_BYTES; i++) {
		for (j = 0; j < 8; j++) {
			if ((rf_code[i] >> j) & 1) {
				rf433_pin_control(scope, first_logic_level);
				_delay_us(400);
				rf433_pin_control(scope, second_logic_level);
				_delay_us(800);
			} else {
				rf433_pin_control(scope, first_logic_level);
				_delay_us(800);
				rf433_pin_control(scope, second_logic_level);
				_delay_us(400);
			}
			
			// Last byte contains only 2 bits
			if (i == (RF433_CODE_BYTES - 1) && j >= 1) {
				break;
			}
		}
	}

	// Guard time 39 Te
	_delay_us(15600);
	
	#if RF433_INVERTED
		rf433_pin_control(scope, 0);
	#endif
}

void rf433_send_next_code(Rf433_Scope *scope, uint8_t times) {
	const uint8_t *rf_code = rf433_get_next_code();
	
	for (uint8_t i = 0; i < times; i++) {
		rf433_send_code(scope, rf_code);
	}
}