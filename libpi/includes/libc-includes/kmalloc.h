#ifndef __KMALLOC_H__
#define __KMALLOC_H__

#include "rpi.h"

/*******************************************************************************
 * simple memory allocation: no free, just have to reboot().
 */

// returns 0-filled memory.
void *kmalloc(unsigned nbytes) ;
void *kmalloc_sketch(unsigned nbytes); // sketchy version that doesn't do checks, but may be faster.
void *kmalloc_aligned(unsigned nbytes, unsigned alignment);

// initialize kmalloc
void kmalloc_init(void);
// initialize and set where the heap starts.
void kmalloc_init_set_start(unsigned _addr);

// return pointer to the first free byte.  used for
// bounds checking.
void *kmalloc_heap_ptr(void);

// currently no-ops.
void kfree(void *p);
void kfree_all(void);

// does [p, p+n) only contain 0s?
int memiszero(const void *_p, unsigned n);


#endif