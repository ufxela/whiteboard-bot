/**
 * Another, differently implemented stepper int library, based off of option 3. Has its benefits and drawbacks. Probably the best option imo.
 */ 
#ifndef __STEPPER3_INT_H__
#define __STEPPER3_INT_H__

#include "stepper.h"

typedef enum {
    STEPPER3_NOT_STARTED,
    STEPPER3_STARTED,
    STEPPER3_FINISHED,
    STEPPER3_ERROR
} stepper3_position_status_t;

typedef struct stepper3_position_t {
    struct stepper3_position_t * next;
    int steps_start; // starting position of this item
    int steps_goal; // goal position of this item
    unsigned start_time; // start time of the position. User can optionally set this (implement later). 0 means unset.
    unsigned usec_between_steps; // time we should wait between any given step.
    stepper3_position_status_t status;
    int sync; // a tag to mark that this isn't an actual position, but a sync position.
    int dir; // -1 for backwards 1 for forwards, 0 for unset
} stepper3_position_t;

#define E stepper3_position_t // BADDD... cause now we can't include syscall-record.h, since it also #define E. Q.h should be refactored s.t. doesn't need to #define E.
#include "Q.h"

typedef struct {
    stepper_t * stepper;
    Q_t positions; // positions for the stepper to go to, can be queued. Will go to positions at speed speed by default.
    unsigned in_job; //0 for no, 1 for yes.
    unsigned synched; // to mark that stepper is currently in a synch position.
} stepper3_int_t;

stepper3_int_t * stepper3_int_a4988_init(unsigned dir, unsigned step);

stepper3_int_t * stepper3_int_a4988_init_with_microsteps(unsigned dir, unsigned step, unsigned MS1, unsigned MS2, unsigned MS3, a4988_microstep_mode_t microstep_mode);

/* retuns the enqueued position. perhaps return the queue of positions instead? */
stepper3_position_t * stepper3_int_enqueue_pos(stepper3_int_t * stepper, int goal_steps, unsigned usec_between_steps);

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
stepper3_position_t * stepper3_int_enqueue_sync(stepper3_int_t * stepper);

int stepper3_int_get_position_in_steps(stepper3_int_t * stepper);

int stepper3_int_is_free(stepper3_int_t * stepper);

#endif