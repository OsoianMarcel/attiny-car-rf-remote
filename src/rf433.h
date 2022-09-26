// Protcol: HCS301 KeeLoq

#ifndef RF433_H_
#define RF433_H_

#include <stdint.h>
#include <util/delay.h>

#define RF433_CODE_BYTES 9
#define RF433_INVERTED 0

struct Rf433_ScopeS {
	volatile uint8_t *DDR;
	volatile uint8_t *PORT;
	uint8_t PIN;
};

typedef struct Rf433_ScopeS Rf433_Scope;

extern const uint8_t rf433_codes[][RF433_CODE_BYTES];
extern const uint8_t rf433_codes_count;

extern void rf433_init(Rf433_Scope *scope);
extern void rf433_uninit(Rf433_Scope *scope);
extern void rf433_send_code(Rf433_Scope *scope, const uint8_t *rf_code);
extern void rf433_send_next_code(Rf433_Scope *scope, uint8_t times);

#endif