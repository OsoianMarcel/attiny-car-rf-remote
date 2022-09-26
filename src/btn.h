#ifndef BTN_H
#define BTN_H

#include <stdint.h>

#define BTN_CLICK_LOW 1
#define BTN_CLICK_HIGH 2

typedef struct Btn_s {
	volatile uint8_t *DDR;
	volatile uint8_t *PORT;
	volatile uint8_t *PIN;
	uint8_t btn_pin;
	uint8_t prev_state;
	uint8_t ticks;
	uint8_t click_ticks;
} Btn_t;

void btn_init(Btn_t *btn);
uint8_t btn_get_state(Btn_t *btn);
uint8_t btn_clicked(Btn_t *btn);

#endif