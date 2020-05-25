#ifndef __SERVO_H__
#define __SERVO_H__

#include "rpi.h"
#include "pwm-output.h"

typedef struct {
    pwm_output_t * pwm_output;
    unsigned min_pulse_width;
    unsigned max_pulse_width;
    unsigned min_angle;
    unsigned max_angle;
} servo_t;

/* you'll have to know your servo's parameters before hand. A starting point is (pin, 1000, 2000, 0, 180) */
servo_t * servo_init(unsigned pin, unsigned min_pulse_width, unsigned max_pulse_width, unsigned min_angle, unsigned max_angle);

/* to help calibrate servo */
void calibrate_servo(servo_t * servo);

/**
 * Writes angle for one period, then immediately returns (takes 20ms)
 * Note: this may not go entirely to the angle. With my servo (yours will be different)
 * the max angle that the servo can travel from one of these calls is ~30 degrees. 
 * plan accordingly.
 */
void servo_go_to_angle(servo_t * servo, unsigned angle);

/* holds angle for duration_usec usecs (blocking) */
void servo_hold_angle_for(servo_t * servo, unsigned angle, unsigned duration_usec);

#endif