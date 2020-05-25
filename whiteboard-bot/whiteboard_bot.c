/* 
bug:

if we are enqueuing a lot of short jobs onto a stepper, and the stepper completes them all immediately, 
there is a race in Q_nelem, since it will be empty when we check, but then something will be pushed, which casues it to assert.
*/
#include "whiteboard_bot.h"

// user can choose these
static unsigned px_size = 1;
static unsigned font_size_px = 400;
static unsigned min_usec_between_steps = 500; //tested up to 125 (works better for curves, not letters)

static wbb_t * inits(){
    delay_ms(100);   // allow time for device to boot up.
    i2c_init(); // ew: this should not be here; should be in accel_init()
    delay_ms(100);   // allow time to settle after init.

    return wbb_init(LEFT_DIR, LEFT_STEP, LEFT_MS1, LEFT_MS2, LEFT_MS3, RIGHT_DIR, RIGHT_STEP, RIGHT_MS1, RIGHT_MS2, RIGHT_MS3, SERVO, SIXTEENTH_STEP, px_size, font_size_px, min_usec_between_steps);
} 

void notmain(){
    output("starting whiteboard bot!\n");

    wbb_t * wbb = inits();
    wbb_shell(wbb);

    output("ending whiteboard bot!\n");
    clean_reboot();
}