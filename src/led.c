#include "led.h"

void led_init(Led *led) {
	*led->DDR |= (1 << led->PIN);
}

void led_uninit(Led *led) {
	*led->DDR &= ~(1 << led->PIN);
	*led->PORT &= ~(1 << led->PIN);
}

void led_on(Led *led) {
	*led->PORT |= (1 << led->PIN);
}

void led_off(Led *led) {
	*led->PORT &= ~(1 << led->PIN);
}

void led_toggle(Led *led) {
	*led->PORT ^= (1 << led->PIN);
}