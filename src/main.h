#ifndef MAIN_H_
#define MAIN_H_


#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

#include "rf433.h"
#include "btn.h"
#include "led.h"

#define NUM_TASKS 4

uint8_t setup(void);
void timer0_init(void);

void reset_task(uint8_t tsk);
void set_task(uint8_t tsk);
void task_dispatch(void);
void task0(void);
void task1(void);
void task2(void);
void task3(void);

#endif