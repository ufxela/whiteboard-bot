#ifndef __STEPPER_H__
#define __STEPPER_H__

#include "rpi.h"
#include "gpio.h"
#include "kmalloc.h"

// designed to be run w/ an h bridge

// const unsigned MIN_STEP_DELAY_US = 1150; //for my stepper, this is the least us between two steps before we start to skip steps.
// todo: 
// microstepping
// set/stop motor position

typedef enum {
    H_BRIDGE,
    A4988
} stepper_driver_t;

typedef enum {
    FULL_STEP,
    HALF_STEP,
    QUARTER_STEP,
    EIGHTH_STEP,
    SIXTEENTH_STEP
} a4988_microstep_mode_t;

typedef struct {
    int step_count;
    unsigned A1;
    unsigned A2;
    unsigned B1;
    unsigned B2;
    unsigned dir;
    unsigned step;
    unsigned MS1;
    unsigned MS2;
    unsigned MS3;
    stepper_driver_t driver;
} stepper_t;

stepper_t * stepper_h_bridge_init(unsigned A1, unsigned A2, unsigned B1, unsigned B2);
stepper_t * stepper_a4988_init(unsigned dir, unsigned step);
stepper_t * stepper_a4988_init_with_microsteps(unsigned dir, unsigned step, unsigned MS1, unsigned MS2, unsigned MS3, a4988_microstep_mode_t microstep_mode);

void stepper_a4988_set_microsteps(stepper_t * stepper, a4988_microstep_mode_t microstep_mode);

void stepper_step_forward(stepper_t * stepper);

void stepper_step_backward(stepper_t * stepper);

int stepper_get_position_in_steps(stepper_t * stepper);

#endif