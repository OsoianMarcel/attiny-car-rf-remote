#ifndef LED_H
#define LED_H

#include <stdint.h>

struct LedS {
	volatile uint8_t *DDR;
	volatile uint8_t *PORT;
	uint8_t PIN;
};

typedef struct LedS Led;

extern void Led_Init(Led *led);
extern void Led_Uninit(Led *led);
extern void Led_On(Led *led);
extern void Led_Off(Led *led);
extern void Led_Toggle(Led *led);

#endif