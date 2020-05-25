#ifndef __SERVO_INT_H
#define __SERVO_INT_H

#include "rpi.h"
#include "pwm-output-int.h"

typedef struct {
    pwm_output_int_t * pwm_output;
    unsigned min_pulse_width;
    unsigned max_pulse_width;
    unsigned min_angle;
    unsigned max_angle;
} servo_int_t;

servo_int_t * servo_int_init(unsigned pin, unsigned min_pulse_width, unsigned max_pulse_width, unsigned min_angle, unsigned max_angle);

void calibrate_servo_int(servo_int_t * servo);

void servo_int_go_to_angle(servo_int_t * servo, unsigned angle);

#endif