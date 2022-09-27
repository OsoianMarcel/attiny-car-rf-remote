#ifndef LED_H
#define LED_H

#include <stdint.h>

struct LedS {
	volatile uint8_t *DDR;
	volatile uint8_t *PORT;
	uint8_t PIN;
};

typedef struct LedS Led;

extern void led_init(Led *led);
extern void led_uninit(Led *led);
extern void led_on(Led *led);
extern void led_off(Led *led);
extern void led_toggle(Led *led);

#endif