#ifndef __STEPPER_INT_H__
#define __STEPPER_INT_H__
 
#include "stepper.h"

/**
 * A fun little library, put the music stuff here
 * 
 * todo: add a tuner function which allows user to tune their stepper
 * Furthermore, make notes array dynamic--it calculates everything on the fly
 * based on the tuner function stuff 
 */

typedef enum {
    A,
    AS,
    B,
    C,
    CS,
    D,
    DS,
    E,
    F,
    FS,
    G,
    GS,
} stepper_tone_t;

typedef struct {
    stepper_tone_t tone;
    unsigned octave;
    unsigned duration;
} stepper_note_t;

void play_notes(stepper_t * stepper, stepper_note_t * notes);

#endif