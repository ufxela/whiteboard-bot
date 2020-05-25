#include "wbb-extra.h"
#include "i2c.h"
#include "lsm6ds33.h"


// weird behavior: without "if(x != 0 && y != 0){", this hangs after a time proportional to nsec, beacuse of a sync issue
// no clue why
void wbb_accel(wbb_t * wbb, unsigned nsecs){
    accel_t h = accel_init(lsm6ds33_default_addr, lsm6ds33_2g, lsm6ds33_416hz);
    unsigned start = timer_get_usec();
    while(timer_get_usec() - start < nsecs * 1000000){
        // output("1");
        imu_xyz_t v = accel_rd(&h);
            // output("2");
        v = accel_scale(&h, v);
        int x = 0;
        int y = 0;
        int z = 0;
        if(v.x > 300 || v.x < -300){
            x = v.x / 100;
        }
        if(v.y > 300 || v.y < -300){
            y = v.y / 100;
        }
        if(v.z > 2500){
            z = 1;
        }else if(v.z < 500){
            z = -1;
        }

        if(x != 0 || y != 0){
            wbb_go_to_coords_relative(wbb, x, y);
        }
            // output("3");
        if(z > 0){
            wbb_lift_pen(wbb);
        }else if(z < 0){
            wbb_place_pen(wbb);
        }
            // output("4");
        wbb_complete(wbb);
        // output("5");

        delay_ms(10); // ugly way to get speed :(
    }
}