#include "btn.h"

void btn_init(Btn_t *btn, uint8_t pullup) {
	// Input mode
	*btn->DDR &= ~(1 << btn->btn_pin); 
	if (pullup) {
		// Activate the internal pull-up resistor
		*btn->PORT |= (1 << btn->btn_pin); 
	}
}

uint8_t btn_get_state(Btn_t *btn) {
	return ((*btn->PIN >> btn->btn_pin) & 1) == 0;
}

uint8_t btn_clicked(Btn_t *btn) {
	uint8_t cur_state = btn_get_state(btn);

	if (cur_state != btn->prev_state) {
		btn->ticks++;
		if (btn->ticks >= btn->click_ticks) {
			btn->prev_state = cur_state;
			btn->ticks = 0;
			
			if (btn->prev_state == 1) {
				return BTN_CLICK_LOW;
			} else {
				return BTN_CLICK_HIGH;
			}
		}
	} else {
		btn->ticks = 0;
	}

	return 0;
}