#ifndef __STEPPER_INT_H__
#define __STEPPER_INT_H__

#include "stepper.h"

/**
 * An interrupt based stepper library
 * 
 * Benefit of interrupts: user doesn't have to manually perform every
 * step, and keep track of time delays between each step.
 * 
 * user can
 * - init and free (note: initting and free kmalloc/kfree and also claim gpio pins once gpio protection is implemented)
 * - step forwards/backwards
 * - get current step position
 * - set minimum time between steps (1150 us default, because that's what works for me)
 * - tell motor to go to a certain step position (option: at a user specified speed)
 * - tell motor to spin at a certain speed (option: for a user specified duration)
 * - control motor torque (not sure if this is possible w/ h bridge)?
 * - stop/kill motor actions
 * - reset motor position
 * - set motor position
 * - set motor default speed (for going to a certain step position)
 * - set motor acceleration parameters
 * - pass in a datastructure with times and positions and have the stepper
 *      adhere to that time table (and assert if time table is impossible)
 * 
 * 
 * Also, still gives user same interface as normal stepper.h
 * 
 * Module keeps track of minimum time between steps and makes an assertion
 * if that minimum time is violated (1150 us for me)
 * 
 * Build this after building better interrupt handler interface
 * 
 * Schedule timer interrupts at every (to be determined quanta) amount
 * of time, and in the stepper interrupt handler, if it's
 * time to step, then step, otherwise do nothing. 
 * 
 * furthermore, by adding in acceleration, we're actually increasing the capabilities of the stepper
 * beacuse now the stepper can accelerate to speed, and thus acheive higher rpms
 * than if we were starting it instantaneously, in which case it would skip steps. 
 *  
 * 
 */

#define STEPPER_INT_MIN_USEC_BETWEEN_STEPS 200 // set this based on your own stepper motor and stuff like microstepping

typedef struct stepper_position_t {
    struct stepper_position_t * next;
    int step_count;
    int speed; //allows user to override their default speed
    int done; //0 if job not done, 1 if done, -1 on error.
} stepper_position_t;

#define E stepper_position_t // BADDD... cause now we can't include syscall-record.h, since it also #define E. Q.h should be refactored s.t. doesn't need to #define E.
#include "Q.h"

typedef struct {
    stepper_t * stepper;
    int speed; // -1 means unset, otherwise must be non negative. Note: higher values for speed => slower.
    int accel; // -1 means unset, otherwise must be non negative
    Q_t positions; // positions for the stepper to go to, can be queued. Will go to positions at speed speed by default.
    unsigned kill; // if not zero, stop stepper.
    unsigned in_job; //0 for no, 1 for yes.
} stepper_int_t;

stepper_int_t * stepper_int_a4988_init(unsigned dir, unsigned step);

stepper_int_t * stepper_int_a4988_init_with_microsteps(unsigned dir, unsigned step, unsigned MS1, unsigned MS2, unsigned MS3, a4988_microstep_mode_t microstep_mode);

// returns -1 on invalid accel
int stepper_int_set_accel(stepper_int_t * stepper, unsigned accel);

// returns -1 on invalid speed
int stepper_int_set_speed(stepper_int_t * stepper, unsigned speed);

/* retuns the enqueued position. perhaps return the queue of positions instead? */
stepper_position_t * stepper_int_enqueue_pos(stepper_int_t * stepper, int steps);

// returns -1 and doesn't go to pos if we're currently in a job
int stepper_int_go_to_pos(stepper_int_t * stepper, int steps);

/* returns null on failure */
stepper_position_t * stepper_int_enqueue_pos_at_time(stepper_int_t * stepper, int steps, unsigned start_time_usec, unsigned end_time_usec);

// does checking to see if we can reach the position at the desired time
// returns -1 if we can't 
int stepper_int_go_to_pos_at_time(stepper_int_t * stepper, int steps, unsigned end_time_usec);

stepper_position_t * stepper_int_enqueue_pos_with_speed(stepper_int_t * stepper, int steps, int speed);

int stepper_int_go_to_pos_with_speed(stepper_int_t * stepper, int steps, int speed);

// returns -1 and doesn't step if stepper currently in a job
int stepper_int_step_forward(stepper_int_t * stepper);

// returns -1 and doesn't step if stepper currently in a job
int stepper_int_step_backward(stepper_int_t * stepper);

int stepper_int_get_position_in_steps(stepper_int_t * stepper);

/* 1 for no current jobs and no enqueued jobs
    0 for either in a current job or there are enqueued jobs
*/
int stepper_int_is_free(stepper_int_t * stepper);

int stepper_get_num_steps(stepper_int_t * stepper);

#endif