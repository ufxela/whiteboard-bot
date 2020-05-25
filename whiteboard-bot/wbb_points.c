#include "wbb-extra.h"

void wbb_go_to_points(wbb_t * wbb, coord_t * coords, unsigned npoints){
    unsigned index = 0;
    while(index < npoints){
        wbb_go_to_coords(wbb, coords[index].x, coords[index].y);
        // printk("going to %d, %d\n", coords[index].x, coords[index].y);
        index++;
    }
}

void wbb_go_to_points_offset(wbb_t * wbb, coord_t * coords, unsigned npoints, unsigned x_off, unsigned y_off){
    unsigned index = 0;
    while(index < npoints){
        wbb_go_to_coords(wbb, coords[index].x + x_off, coords[index].y + y_off);
        index++;
    }
}