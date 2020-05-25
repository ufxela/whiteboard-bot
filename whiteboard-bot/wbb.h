#include "rpi.h"
#include "stepper.h"
#include "servo.h"

typedef struct {
    int x,y;
} coord_t;

typedef struct {
    stepper_t * left_stepper;
    stepper_t * right_stepper;
    servo_t * servo;
    coord_t curr_stepper_pos; // x is left stepper, y is right stepper
    coord_t curr_cartesian_pos;
    unsigned steps_per_px;
    unsigned font_px;
    unsigned min_usec_between_steps;
} wbb_t;

wbb_t * wbb_init(unsigned left_dir, unsigned left_step, unsigned left_ms1, unsigned left_ms2, unsigned left_ms3, 
        unsigned right_dir, unsigned right_step, unsigned right_ms1, unsigned right_ms2, unsigned right_ms3, 
        unsigned servo, a4988_microstep_mode_t step_mode, unsigned steps_per_px, unsigned font_px, unsigned min_usec_between_steps);

void wbb_lift_pen(wbb_t * wbb);

void wbb_place_pen(wbb_t * wbb);

void wbb_go_to_coords_relative(wbb_t * wbb, int dx, int dy);

void wbb_go_to_coords(wbb_t * wbb, int new_x, int new_y);

// 0 for in job, 1 for free
int wbb_is_free(wbb_t * wbb);

void wbb_complete(wbb_t * wbb);

coord_t wbb_get_pos(wbb_t * wbb);