#include "wbb.h"

void wbb_go_to_points(wbb_t * wbb, coord_t * coords, unsigned npoints);

void wbb_go_to_points_offset(wbb_t * wbb, coord_t * coords, unsigned npoints, unsigned x_off, unsigned y_off);

/* note: this isn't great cause it's statically generated. Works better for smaller circles than it does for larger. */
void wbb_draw_circle(wbb_t * wbb, unsigned radius, unsigned npoints);

/* 
draws an arc that contains npoints points per circumference, 
starting at start_point and ending at end_point (note: start/end point can be negative 
and they wrap, modulo npoints.

fun: can be used to draw n-gons wbb_draw_arc(wbb, radius, n, 0, n+1);
*/
void wbb_draw_arc(wbb_t * wbb, unsigned radius, unsigned points_per_circ, int start_point, int end_point);

void wbb_go_home(wbb_t * wbb);

void wbb_draw_letters(wbb_t * wbb, char * letters);

void wbb_accel(wbb_t * wbb, unsigned nsecs);

void wbb_shell(wbb_t * wbb);

void wbb_server(wbb_t * wbb);