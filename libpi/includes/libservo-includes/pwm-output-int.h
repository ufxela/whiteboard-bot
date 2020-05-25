#ifndef __PWM_OUTPUT_INT_H
#define __PWM_OUTPUT_INT_H

#include "rpi.h"

typedef struct {
    unsigned pin;    
    unsigned period_usec;
    unsigned curr_duty_cycle_usec;
    unsigned prev_write_time_usec;
    unsigned prev_write_val;
} pwm_output_int_t;

pwm_output_int_t * pwm_output_int_init(unsigned pin, unsigned period_usec);

void pwm_output_int_destroy(pwm_output_int_t * pwm_output);

void pwm_output_int_set_curr_duty_cycle(pwm_output_int_t * pwm_output, unsigned new_duty_cycle_usec);

#endif