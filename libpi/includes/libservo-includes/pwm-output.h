#ifndef __PWM_OUTPUT_H__
#define __PWM_OUTPUT_H__

#include "rpi.h"

typedef struct {
    unsigned pin;
    unsigned period_usec;
} pwm_output_t;

pwm_output_t * pwm_output_init(unsigned pin, unsigned period_usec);

// blocking. Writes num_periods whole periods
void pwm_output_write_duty_cycle_for_periods(pwm_output_t * pwm_output, unsigned duty_cycle_usec, unsigned num_periods);

// blocking. Returns exactly after duration_usec usecs (even if in middle of a period)
void pwm_output_write_duty_cycle_for_duration_usec(pwm_output_t * pwm_output, unsigned duty_cycle_usec, unsigned duration_usec);

#endif