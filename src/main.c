#include "main.h"

char task_bits = 0;
uint8_t halfSecs = 0;
volatile uint8_t tick_flag = 0;
unsigned int task_timers[NUM_TASKS] = {0,0,0,0};
static const PROGMEM char bit_mask[] = {1,2,4,8};

Rf433_Scope rf433_scope;
Btn_t btn;
Led led;

void task_dispatch(void) {
	uint8_t task;

	task = 0;
	while (task < NUM_TASKS) {
		if (task_timers[task]) {
  			task_timers[task]--;
			if (task_timers[task] == 0) {
				set_task(task);
			}
		}
		task++;
	}

	task = 0;
	while (task < NUM_TASKS) {
		if ((task_bits & pgm_read_byte(&bit_mask[task]))) {
	  		break;
		}
		task++;
	}
	
	switch(task)
	{
		case 0:
			task0();
			break;
		case 1:
			task1();
			break;
		case 2:
			task2();
			break;
		case 3:
			task3();
			break;
	}                       
}

void set_task(uint8_t tsk) {
	task_bits |= pgm_read_byte(&bit_mask[tsk]);
}

void reset_task(uint8_t tsk) {
	task_bits &= (~pgm_read_byte(&bit_mask[tsk]));
}

void task0(void) {
	if (btn_clicked(&btn) == BTN_CLICK_HIGH) {
		set_task(1);
	}
	
	task_timers[0] = 4;
	reset_task(0);
}

void task1(void) {
	led_on(&led);
	rf433_send_next_code(&rf433_scope, 3);
	led_off(&led);
	reset_task(1);
}

void task2(void) {
	if (halfSecs == 0) {
		led_on(&led);
	} else if (halfSecs == 1) {
		led_off(&led);
	}
	
	// 0.5 sec * 60 = ~30 sec
	if (halfSecs >= 60) {
		halfSecs = 0;
	} else {
		halfSecs++;
	}
	
	task_timers[2] = 255;
	reset_task(2);
}

void task3(void) {
	reset_task(3);
}

void timer0_init(void) {
	TCNT0 = 0; // Reset timer value
	TCCR0B |= (1 << CS01) | (1 << CS00); // Clock select /64 (overflow once in (1 / (8e6 / 64) * 255 * 1e3) = 2 ms)
	TIMSK |= (1 << TOIE0); // Allow overflow interrupt
}

uint8_t setup(void) {
	cli();
	
	rf433_scope = (Rf433_Scope){&DDRB, &PORTB, PB4};
	rf433_init(&rf433_scope);
	
	btn = (Btn_t){
		.DDR = &DDRB,
		.PORT = &PORTB,
		.PIN = &PINB,
		.btn_pin = PB0,
		.click_ticks = 4,
		.prev_state = 0,
		.ticks = 0
	};
	btn_init(&btn, 0);
	
	led = (Led){
		.DDR = &DDRB,
		.PORT = &PORTB,
		.PIN = PB3
	};
	led_init(&led);
	
	timer0_init();
	
	set_task(0);
	set_task(2);
	
	sei();
	
	return 0;
}

ISR(TIMER0_OVF_vect) {
	tick_flag = 1;
}

int main(void)
{
	setup();
	
    while (1) {		
	    if (tick_flag) {
		    tick_flag = 0;
		    task_dispatch();
	    }
    }
	
	return 0;
}

