#ifndef __TIMER_INTERRUPT_H__
#define __TIMER_INTERRUPT_H__

#include "rpi.h"
#include "rpi-armtimer.h"
#include "rpi-interrupts.h"

void timer_interrupt_init(unsigned ncycles);

// returns 1 if timer interrupt, 0 if not.
unsigned check_and_clear_timer_int();

unsigned check_timer_int();

void clear_timer_int();

#endif
