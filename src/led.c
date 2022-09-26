#include "led.h"

void Led_Init(Led *led) {
	*led->DDR |= (1 << led->PIN);
}

void Led_Uninit(Led *led) {
	*led->DDR &= ~(1 << led->PIN);
	*led->PORT &= ~(1 << led->PIN);
}

void Led_On(Led *led) {
	*led->PORT |= (1 << led->PIN);
}

void Led_Off(Led *led) {
	*led->PORT &= ~(1 << led->PIN);
}

void Led_Toggle(Led *led) {
	*led->PORT ^= (1 << led->PIN);
}