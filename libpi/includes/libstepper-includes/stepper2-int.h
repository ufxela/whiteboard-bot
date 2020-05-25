/**
 * Another, differently implemented stepper int library, based off of option 1. Has its benefits and drawbacks.
 */ 
#ifndef __STEPPER2_INT_H__
#define __STEPPER2_INT_H__

#include "stepper.h"

typedef struct stepper2_position_t {
    struct stepper2_position_t * next;
    int steps;
    unsigned usec_between_steps;
    unsigned time_at_prev_step;
    int done; //0 if job not done, 1 if done, -1 on error.
    int sync; // a tag to mark that this isn't an actual position, but a sync position.
} stepper2_position_t;

#define E stepper2_position_t // BADDD... cause now we can't include syscall-record.h, since it also #define E. Q.h should be refactored s.t. doesn't need to #define E.
#include "Q.h"

typedef struct {
    stepper_t * stepper;
    Q_t positions; // positions for the stepper to go to, can be queued. Will go to positions at speed speed by default.
    unsigned in_job; //0 for no, 1 for yes.
    unsigned synched;
} stepper2_int_t;

stepper2_int_t * stepper2_int_a4988_init(unsigned dir, unsigned step);

stepper2_int_t * stepper2_int_a4988_init_with_microsteps(unsigned dir, unsigned step, unsigned MS1, unsigned MS2, unsigned MS3, a4988_microstep_mode_t microstep_mode);

/* retuns the enqueued position. perhaps return the queue of positions instead? */
stepper2_position_t * stepper2_int_enqueue_pos(stepper2_int_t * stepper, int goal_steps, unsigned usec_between_steps);

/**
 * This is for syncing multiple stepper motors. 
 * 
 * If a stepper is sent a sync position, once the stepper gets to that
 * position in the queue, it will sit there and wait for all other steppers
 * to also enter a sync position. once that occurs, it will restart, at the next
 * position.
 * 
 * Does nothing if you only have one stepper
 */ 
stepper2_position_t * stepper2_int_enqueue_sync(stepper2_int_t * stepper);

int stepper2_int_get_position_in_steps(stepper2_int_t * stepper);

int stepper2_int_is_free(stepper2_int_t * stepper);

#endif