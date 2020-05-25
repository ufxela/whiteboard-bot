#include "wbb.h"
#include "kmalloc.h"
#include "math-helpers.h"

static unsigned wbb_get_left_usec_between_steps(wbb_t * wbb, int left_movement, int right_movement){
    if(abs(left_movement) > abs(right_movement)){
        return wbb->min_usec_between_steps;
    }else if(left_movement == 0){
        return wbb->min_usec_between_steps;
    }else{
        return divide(wbb->min_usec_between_steps * abs(right_movement), abs(left_movement));
    }
}

static unsigned wbb_get_right_usec_between_steps(wbb_t * wbb, int left_movement, int right_movement){
    if(abs(right_movement) > abs(left_movement)){
        return wbb->min_usec_between_steps;
    }else if(right_movement == 0){
        return wbb->min_usec_between_steps;
    }else{
        return divide(wbb->min_usec_between_steps * abs(left_movement), abs(right_movement));
    }
}

static void wbb_sync(wbb_t * wbb){
    
}

wbb_t * wbb_init(unsigned left_dir, unsigned left_step, unsigned left_ms1, unsigned left_ms2, unsigned left_ms3, 
        unsigned right_dir, unsigned right_step, unsigned right_ms1, unsigned right_ms2, unsigned right_ms3, 
        unsigned servo, a4988_microstep_mode_t step_mode, unsigned steps_per_px, unsigned font_px, unsigned min_usec_between_steps){
    kmalloc_init();
    wbb_t * wbb = kmalloc(sizeof(wbb_t));
    wbb->left_stepper = stepper_a4988_init_with_microsteps(left_dir, left_step, left_ms1, left_ms2, left_ms3, step_mode);
    wbb->right_stepper = stepper_a4988_init_with_microsteps(right_dir, right_step, right_ms1, right_ms2, right_ms3, step_mode);
    wbb->servo = servo_init(servo, 1000, 2000, 8, 180);
    wbb->curr_stepper_pos = (coord_t) {0, 0};
    wbb->curr_cartesian_pos = (coord_t) {0, 0};
    wbb->steps_per_px = steps_per_px;
    wbb->font_px = font_px;
    wbb->min_usec_between_steps = min_usec_between_steps;
    return wbb;
}

void wbb_lift_pen(wbb_t * wbb){
    wbb_complete(wbb);
    for(int i = 0; i < 10; i++){
        servo_go_to_angle(wbb->servo, 80);
    }
}

void wbb_place_pen(wbb_t * wbb){
    wbb_complete(wbb);
    for(int i = 0; i < 10; i++){
        servo_go_to_angle(wbb->servo, 180);
    }
}

void wbb_go_to_coords_relative(wbb_t * wbb, int dx, int dy){
    wbb->curr_cartesian_pos.x += dx;
    wbb->curr_cartesian_pos.y += dy;
    int left_movement = (dx + dy) * wbb->steps_per_px; 
    int right_movement = (dx - dy) * wbb->steps_per_px; 
    wbb->curr_stepper_pos.x += left_movement;
    wbb->curr_stepper_pos.y += right_movement;
    unsigned usec_between_left_steps = wbb_get_left_usec_between_steps(wbb, left_movement, right_movement);
    unsigned usec_between_right_steps = wbb_get_right_usec_between_steps(wbb, left_movement, right_movement);
    int curr_left_pos = 0;
    int curr_right_pos = 0;
    //ugly implementation for now; should switch over to stepper int 3 version
    unsigned start_usec = timer_get_usec();
    unsigned usec_at_last_left_step = start_usec;
    unsigned usec_at_last_right_step = start_usec;
    while(1){
        unsigned curr_usec = timer_get_usec();

        if(curr_left_pos != left_movement && curr_usec - usec_at_last_left_step > usec_between_left_steps){
            usec_at_last_left_step = curr_usec;
            if(left_movement < 0){
                curr_left_pos--;
                stepper_step_backward(wbb->left_stepper);
            }else{
                curr_left_pos++;
                stepper_step_forward(wbb->left_stepper);
            }
        }

        if(curr_right_pos != right_movement && curr_usec - usec_at_last_right_step > usec_between_right_steps){
            usec_at_last_right_step = curr_usec;
            if(right_movement < 0){
                curr_right_pos--;
                stepper_step_backward(wbb->right_stepper);
            }else{
                curr_right_pos++;
                stepper_step_forward(wbb->right_stepper);
            }
        }

        if(curr_left_pos == left_movement && curr_right_pos == right_movement){
            break;
        }
    }
}

void wbb_go_to_coords(wbb_t * wbb, int new_x, int new_y){
    wbb_go_to_coords_relative(wbb, new_x - wbb->curr_cartesian_pos.x, new_y - wbb->curr_cartesian_pos.y);
}

int wbb_is_free(wbb_t * wbb){
    return 1;
}

void wbb_complete(wbb_t * wbb){
    while(!wbb_is_free(wbb)){/*wait*/}
}

coord_t wbb_get_pos(wbb_t * wbb){
    printk("%d %d\n", wbb->curr_stepper_pos);
    return wbb->curr_cartesian_pos;
}